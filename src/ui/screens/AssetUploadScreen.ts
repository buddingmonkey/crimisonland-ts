/**
 * AssetUploadScreen.ts - First-run upload screen for PAQ game files
 *
 * Renders a DOM-based UI (before PixiJS initializes) with a single drop zone.
 * Players drop both crimson.paq and sfx.paq into one area. A checklist below
 * shows validation status for each file. CRC32 validation warns (soft block)
 * if files don't match expected checksums.
 */

/** Expected PAQ file specifications */
const EXPECTED_FILES: Record<string, { crc32: number; label: string }> = {
    'crimson.paq': { crc32: 0x5e1b2506, label: 'crimson.paq' },
    'sfx.paq': { crc32: 0x4cbc6c82, label: 'sfx.paq' },
};

/** PAQ magic bytes: "paq\0" */
const PAQ_MAGIC = [0x70, 0x61, 0x71, 0x00];

export interface UploadResult {
    crimsonPaq: ArrayBuffer;
    sfxPaq: ArrayBuffer;
}

/** Validate that an ArrayBuffer starts with PAQ magic bytes. */
function isPaqFile(data: ArrayBuffer): boolean {
    if (data.byteLength < 4) return false;
    const view = new Uint8Array(data, 0, 4);
    return view[0] === PAQ_MAGIC[0] && view[1] === PAQ_MAGIC[1] && view[2] === PAQ_MAGIC[2] && view[3] === PAQ_MAGIC[3];
}

/** Compute CRC32 checksum. */
function crc32(buf: Uint8Array): number {
    const table = new Uint32Array(256);
    for (let i = 0; i < 256; i++) {
        let c = i;
        for (let j = 0; j < 8; j++) c = c & 1 ? 0xedb88320 ^ (c >>> 1) : c >>> 1;
        table[i] = c;
    }
    let crc = 0xffffffff;
    for (let i = 0; i < buf.length; i++) crc = table[(crc ^ buf[i]) & 0xff] ^ (crc >>> 8);
    return (crc ^ 0xffffffff) >>> 0;
}

/** Format file size for display. */
function formatSize(bytes: number): string {
    if (bytes < 1024) return `${bytes} B`;
    if (bytes < 1024 * 1024) return `${(bytes / 1024).toFixed(1)} KB`;
    return `${(bytes / (1024 * 1024)).toFixed(1)} MB`;
}

/**
 * Show the asset upload screen and wait for the user to provide both PAQ files.
 * @returns Promise that resolves with the uploaded file data
 */
export function showUploadScreen(): Promise<UploadResult> {
    return new Promise((resolve) => {
        const files: Record<string, ArrayBuffer> = {};
        const warnings: Set<string> = new Set();

        // Create container
        const container = document.createElement('div');
        container.id = 'upload-screen';
        container.innerHTML = `
            <div class="upload-content">
                <h1 class="upload-title">Crimsonland <span class="upload-year">2003</span></h1>
                <p class="upload-subtitle">To play, you'll need the original game data files.</p>

                <div class="drop-zone" id="drop-zone">
                    <div class="drop-zone-icon">📂</div>
                    <div class="drop-zone-text">Drop <strong>crimson.paq</strong> and <strong>sfx.paq</strong> here</div>
                    <div class="drop-zone-hint">or click to browse</div>
                    <input type="file" class="drop-zone-input" id="file-input" multiple accept=".paq" />
                </div>

                <p class="upload-purchase-info">
                    If you do not have the original .paq files you can purchase the game on
                    <a href="https://www.gog.com/en/game/crimsonland" target="_blank" rel="noopener noreferrer">GOG</a>.
                    Once you have purchased the game, see
                    <a href="#" id="open-guide-link">this guide</a>
                    for instructions on how to find the .paq files.
                </p>

                <!-- Guide Modal -->
                <div class="guide-modal-overlay" id="guide-modal" style="display:none">
                    <div class="guide-modal">
                        <button class="guide-modal-close" id="guide-modal-close" aria-label="Close">&times;</button>
                        <h2 class="guide-modal-title">Finding the PAQ Files</h2>
                        <div class="guide-modal-body">
                            <p>You must install <strong>Crimsonland Classic</strong> from GOG (not the remake).</p>
                            <ol>
                                <li>In the <a href="https://www.gog.com/en/game/crimsonland" target="_blank" rel="noopener noreferrer">GOG web page</a> or <strong>GOG Galaxy</strong> interface, navigate to your games and open the Crimsonland page.</li>
                                <li>Select the <strong>Extras</strong> tab and download <strong>&ldquo;Crimsonland &ndash; Crimsonland Classic&rdquo;</strong>.</li>
                                <li>Run the installer: <code>setup_crimsonland_classic_2.0.0.4.exe</code></li>
                                <li>When installation completes, open the folder you selected during setup.<br/>Typically: <code>C:\\GOG Games\\Crimsonland Classic</code></li>
                                <li>The <code>crimson.paq</code> and <code>sfx.paq</code> files will be in that folder.</li>
                            </ol>
                        </div>
                    </div>
                </div>

                <div class="file-checklist" id="file-checklist">
                    <div class="file-item" id="item-crimson" data-file="crimson.paq">
                        <span class="file-icon">☐</span>
                        <span class="file-name">crimson.paq</span>
                        <span class="file-status"></span>
                    </div>
                    <div class="file-item" id="item-sfx" data-file="sfx.paq">
                        <span class="file-icon">☐</span>
                        <span class="file-name">sfx.paq</span>
                        <span class="file-status"></span>
                    </div>
                </div>

                <div class="upload-warning" id="crc-warning" style="display:none">
                    ⚠ One or more files may not be the correct version. The game may not work properly.
                </div>

                <button class="upload-start" id="btn-start" disabled>
                    Start Game
                </button>
            </div>
        `;

        document.body.appendChild(container);

        const dropZone = container.querySelector('#drop-zone') as HTMLElement;
        const fileInput = container.querySelector('#file-input') as HTMLInputElement;
        const btnStart = container.querySelector('#btn-start') as HTMLButtonElement;
        const crcWarning = container.querySelector('#crc-warning') as HTMLElement;

        // Guide modal
        const guideModal = container.querySelector('#guide-modal') as HTMLElement;
        const openGuideLink = container.querySelector('#open-guide-link') as HTMLAnchorElement;
        const closeGuideBtn = container.querySelector('#guide-modal-close') as HTMLButtonElement;

        openGuideLink.addEventListener('click', (e) => {
            e.preventDefault();
            guideModal.style.display = 'flex';
        });

        closeGuideBtn.addEventListener('click', () => {
            guideModal.style.display = 'none';
        });

        guideModal.addEventListener('click', (e) => {
            if (e.target === guideModal) guideModal.style.display = 'none';
        });

        function updateUI() {
            const allPresent = 'crimson.paq' in files && 'sfx.paq' in files;
            btnStart.disabled = !allPresent;

            crcWarning.style.display = warnings.size > 0 ? 'block' : 'none';
        }

        function setItemState(name: string, state: 'valid' | 'warning' | 'error', statusText: string) {
            const key = name === 'crimson.paq' ? 'crimson' : 'sfx';
            const item = container.querySelector(`#item-${key}`) as HTMLElement;
            if (!item) return;

            const icon = item.querySelector('.file-icon') as HTMLElement;
            const status = item.querySelector('.file-status') as HTMLElement;

            item.className = `file-item ${state}`;
            if (state === 'valid') icon.textContent = '✓';
            else if (state === 'warning') icon.textContent = '⚠';
            else icon.textContent = '✗';
            status.textContent = statusText;
        }

        function processFile(file: File) {
            const name = file.name.toLowerCase();
            const spec = EXPECTED_FILES[name];

            if (!spec) {
                // Not a recognized filename — show brief error on the drop zone
                dropZone.classList.add('error');
                const text = dropZone.querySelector('.drop-zone-text') as HTMLElement;
                const prev = text.textContent;
                text.textContent = `"${file.name}" is not a recognized file`;
                setTimeout(() => {
                    dropZone.classList.remove('error');
                    text.innerHTML = 'Drop <strong>crimson.paq</strong> and <strong>sfx.paq</strong> here';
                    void prev; // suppress unused warning
                }, 2500);
                return;
            }

            const reader = new FileReader();
            reader.onload = () => {
                const buffer = reader.result as ArrayBuffer;

                // Validate PAQ magic bytes
                if (!isPaqFile(buffer)) {
                    setItemState(name, 'error', 'Not a valid PAQ file');
                    return;
                }

                // CRC32 validation
                const actual = crc32(new Uint8Array(buffer));
                if (actual !== spec.crc32) {
                    warnings.add(name);
                    setItemState(name, 'warning', `${formatSize(buffer.byteLength)} — CRC mismatch`);
                } else {
                    warnings.delete(name);
                    setItemState(name, 'valid', formatSize(buffer.byteLength));
                }

                files[name] = buffer;
                updateUI();
            };

            reader.onerror = () => {
                setItemState(name, 'error', 'Read failed');
            };

            reader.readAsArrayBuffer(file);
        }

        function handleFiles(fileList: FileList) {
            for (let i = 0; i < fileList.length; i++) {
                processFile(fileList[i]);
            }
        }

        // Click to browse
        dropZone.addEventListener('click', (e) => {
            if ((e.target as HTMLElement).tagName !== 'INPUT') {
                fileInput.click();
            }
        });

        fileInput.addEventListener('change', () => {
            if (fileInput.files) handleFiles(fileInput.files);
        });

        // Drag and drop
        dropZone.addEventListener('dragover', (e) => {
            e.preventDefault();
            e.stopPropagation();
            dropZone.classList.add('dragover');
        });

        dropZone.addEventListener('dragleave', (e) => {
            e.preventDefault();
            e.stopPropagation();
            dropZone.classList.remove('dragover');
        });

        dropZone.addEventListener('drop', (e) => {
            e.preventDefault();
            e.stopPropagation();
            dropZone.classList.remove('dragover');
            if (e.dataTransfer?.files) handleFiles(e.dataTransfer.files);
        });

        // Prevent full-page drop
        document.addEventListener('dragover', (e) => e.preventDefault());
        document.addEventListener('drop', (e) => e.preventDefault());

        // Start button
        btnStart.addEventListener('click', () => {
            if (files['crimson.paq'] && files['sfx.paq']) {
                container.remove();
                resolve({
                    crimsonPaq: files['crimson.paq'],
                    sfxPaq: files['sfx.paq'],
                });
            }
        });
    });
}
