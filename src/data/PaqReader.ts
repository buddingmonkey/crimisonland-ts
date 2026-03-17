/**
 * PaqReader.ts - PAQ archive format reader/writer for Crimsonland
 *
 * File layout:
 *   - magic: 4 bytes, ASCII "paq\0"
 *   - entries: repeated until EOF
 *       - name: NUL-terminated UTF-8 string (relative path)
 *       - size: u32 little-endian payload size
 *       - payload: raw file bytes of length `size`
 */

export const PAQ_MAGIC = new Uint8Array([0x70, 0x61, 0x71, 0x00]); // "paq\0"

export interface PaqEntry {
    name: string;
    data: Uint8Array;
}

/**
 * Read a NUL-terminated UTF-8 string from a DataView at the given offset.
 * Returns the string and the number of bytes consumed (including NUL).
 */
function readCString(view: DataView, offset: number): [string, number] {
    const bytes: number[] = [];
    let i = offset;
    while (i < view.byteLength) {
        const byte = view.getUint8(i);
        i++;
        if (byte === 0) break;
        bytes.push(byte);
    }
    const decoder = new TextDecoder('utf-8');
    const str = decoder.decode(new Uint8Array(bytes));
    return [str, i - offset];
}

/**
 * Write a NUL-terminated UTF-8 string to a Uint8Array.
 * Returns the encoded bytes including NUL terminator.
 */
function writeCString(str: string): Uint8Array {
    const encoder = new TextEncoder();
    const encoded = encoder.encode(str);
    const result = new Uint8Array(encoded.length + 1);
    result.set(encoded);
    result[encoded.length] = 0;
    return result;
}

/**
 * Parse a PAQ archive from raw bytes.
 * @param data - The raw PAQ file data
 * @returns Array of entries with name and data
 * @throws Error if magic bytes are invalid
 */
export function readPaq(data: ArrayBuffer): PaqEntry[] {
    const view = new DataView(data);
    const entries: PaqEntry[] = [];

    // Validate magic bytes
    if (data.byteLength < 4) {
        throw new Error('PAQ file too small: missing magic header');
    }
    for (let i = 0; i < 4; i++) {
        if (view.getUint8(i) !== PAQ_MAGIC[i]) {
            throw new Error('Invalid PAQ file: bad magic bytes');
        }
    }

    let offset = 4; // Skip magic

    while (offset < data.byteLength) {
        // Read NUL-terminated name
        const [name, nameLen] = readCString(view, offset);
        offset += nameLen;

        if (offset + 4 > data.byteLength) {
            break; // Not enough bytes for size field
        }

        // Read size (u32 little-endian)
        const size = view.getUint32(offset, true);
        offset += 4;

        if (offset + size > data.byteLength) {
            throw new Error(`PAQ entry "${name}" claims ${size} bytes but only ${data.byteLength - offset} available`);
        }

        // Read payload
        const payload = new Uint8Array(data, offset, size);
        offset += size;

        entries.push({
            name,
            data: new Uint8Array(payload), // Copy to avoid referencing original buffer
        });
    }

    return entries;
}

/**
 * Find and return a specific entry from a PAQ archive.
 * @param data - The raw PAQ file data
 * @param name - The entry name to find
 * @returns The entry data, or null if not found
 */
export function readPaqEntry(data: ArrayBuffer, name: string): Uint8Array | null {
    const entries = readPaq(data);
    const entry = entries.find((e) => e.name === name);
    return entry ? entry.data : null;
}

/**
 * Create an iterator over PAQ entries without loading all into memory.
 * @param data - The raw PAQ file data
 */
export function* iterPaq(data: ArrayBuffer): Generator<PaqEntry> {
    const view = new DataView(data);

    // Validate magic bytes
    if (data.byteLength < 4) {
        throw new Error('PAQ file too small: missing magic header');
    }
    for (let i = 0; i < 4; i++) {
        if (view.getUint8(i) !== PAQ_MAGIC[i]) {
            throw new Error('Invalid PAQ file: bad magic bytes');
        }
    }

    let offset = 4;

    while (offset < data.byteLength) {
        const [name, nameLen] = readCString(view, offset);
        offset += nameLen;

        if (offset + 4 > data.byteLength) break;

        const size = view.getUint32(offset, true);
        offset += 4;

        if (offset + size > data.byteLength) {
            throw new Error(`PAQ entry "${name}" claims ${size} bytes but only ${data.byteLength - offset} available`);
        }

        const payload = new Uint8Array(data, offset, size);
        offset += size;

        yield { name, data: new Uint8Array(payload) };
    }
}

/**
 * Build a PAQ archive from entries.
 * @param entries - Array of entries to pack
 * @returns The PAQ file as an ArrayBuffer
 */
export function writePaq(entries: PaqEntry[]): ArrayBuffer {
    // Calculate total size
    let totalSize = 4; // Magic
    const encodedNames: Uint8Array[] = [];

    for (const entry of entries) {
        const nameBytes = writeCString(entry.name);
        encodedNames.push(nameBytes);
        totalSize += nameBytes.length + 4 + entry.data.length;
    }

    // Build buffer
    const buffer = new ArrayBuffer(totalSize);
    const view = new DataView(buffer);
    const bytes = new Uint8Array(buffer);

    // Write magic
    bytes.set(PAQ_MAGIC, 0);
    let offset = 4;

    // Write entries
    for (let i = 0; i < entries.length; i++) {
        const entry = entries[i];
        const nameBytes = encodedNames[i];

        // Write name
        bytes.set(nameBytes, offset);
        offset += nameBytes.length;

        // Write size
        view.setUint32(offset, entry.data.length, true);
        offset += 4;

        // Write payload
        bytes.set(entry.data, offset);
        offset += entry.data.length;
    }

    return buffer;
}

/**
 * List all entry names in a PAQ archive.
 * @param data - The raw PAQ file data
 * @returns Array of entry names
 */
export function listPaq(data: ArrayBuffer): string[] {
    return readPaq(data).map((e) => e.name);
}
