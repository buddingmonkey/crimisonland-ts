/**
 * AssetStorage.ts - IndexedDB persistence for PAQ game asset files
 *
 * Stores uploaded PAQ files in IndexedDB so the player only needs
 * to upload once. On subsequent visits, assets load directly from
 * the browser's persistent storage.
 */

const DB_NAME = 'crimsonland-assets';
const DB_VERSION = 1;
const STORE_NAME = 'paq-files';

/**
 * Open (or create) the IndexedDB database.
 */
function openDB(): Promise<IDBDatabase> {
    return new Promise((resolve, reject) => {
        const request = indexedDB.open(DB_NAME, DB_VERSION);

        request.onupgradeneeded = () => {
            const db = request.result;
            if (!db.objectStoreNames.contains(STORE_NAME)) {
                db.createObjectStore(STORE_NAME);
            }
        };

        request.onsuccess = () => resolve(request.result);
        request.onerror = () => reject(request.error);
    });
}

/**
 * Check if both required PAQ files (crimson.paq and sfx.paq) are stored.
 */
export async function hasStoredAssets(): Promise<boolean> {
    try {
        const db = await openDB();
        const tx = db.transaction(STORE_NAME, 'readonly');
        const store = tx.objectStore(STORE_NAME);

        const [crimson, sfx] = await Promise.all([
            new Promise<boolean>((resolve) => {
                const req = store.getKey('crimson.paq');
                req.onsuccess = () => resolve(req.result !== undefined);
                req.onerror = () => resolve(false);
            }),
            new Promise<boolean>((resolve) => {
                const req = store.getKey('sfx.paq');
                req.onsuccess = () => resolve(req.result !== undefined);
                req.onerror = () => resolve(false);
            }),
        ]);

        db.close();
        return crimson && sfx;
    } catch {
        return false;
    }
}

/**
 * Retrieve a stored asset by name.
 * @param name - Key name (e.g. 'crimson.paq')
 * @returns The stored ArrayBuffer, or null if not found
 */
export async function getStoredAsset(name: string): Promise<ArrayBuffer | null> {
    try {
        const db = await openDB();
        const tx = db.transaction(STORE_NAME, 'readonly');
        const store = tx.objectStore(STORE_NAME);

        return new Promise((resolve) => {
            const req = store.get(name);
            req.onsuccess = () => {
                db.close();
                resolve(req.result ?? null);
            };
            req.onerror = () => {
                db.close();
                resolve(null);
            };
        });
    } catch {
        return null;
    }
}

/**
 * Store an asset in IndexedDB.
 * @param name - Key name (e.g. 'crimson.paq')
 * @param data - The file data as an ArrayBuffer
 */
export async function storeAsset(name: string, data: ArrayBuffer): Promise<void> {
    const db = await openDB();
    const tx = db.transaction(STORE_NAME, 'readwrite');
    const store = tx.objectStore(STORE_NAME);

    await new Promise<void>((resolve, reject) => {
        const req = store.put(data, name);
        req.onsuccess = () => resolve();
        req.onerror = () => reject(req.error);
    });

    db.close();

    // Request durable storage so the browser doesn't evict our data
    try {
        if (navigator.storage?.persist) {
            await navigator.storage.persist();
        }
    } catch {
        // Non-critical — storage may still work without persistence guarantee
    }
}

/**
 * Remove all stored assets from IndexedDB.
 */
export async function clearStoredAssets(): Promise<void> {
    try {
        const db = await openDB();
        const tx = db.transaction(STORE_NAME, 'readwrite');
        const store = tx.objectStore(STORE_NAME);

        await new Promise<void>((resolve, reject) => {
            const req = store.clear();
            req.onsuccess = () => resolve();
            req.onerror = () => reject(req.error);
        });

        db.close();
    } catch {
        // Silently fail — clearing is best-effort
    }
}
