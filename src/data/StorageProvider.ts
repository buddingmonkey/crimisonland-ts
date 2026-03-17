/**
 * StorageProvider.ts - Browser storage abstraction
 *
 * Simple localStorage wrapper with JSON serialization.
 * Includes memory fallback for private browsing mode.
 */

/**
 * Storage provider interface (synchronous since localStorage is sync)
 */
export interface StorageProvider {
    /**
     * Get a value from storage
     * @param key Storage key
     * @returns Parsed value or null if not found
     */
    get<T>(key: string): T | null;

    /**
     * Set a value in storage
     * @param key Storage key
     * @param value Value to store (will be JSON serialized)
     */
    set<T>(key: string, value: T): void;

    /**
     * Remove a value from storage
     * @param key Storage key
     */
    remove(key: string): void;

    /**
     * Clear all values from storage
     */
    clear(): void;
}

/**
 * localStorage-based storage provider with JSON serialization
 */
export class LocalStorageProvider implements StorageProvider {
    get<T>(key: string): T | null {
        try {
            const value = localStorage.getItem(key);
            if (value === null) {
                return null;
            }
            return JSON.parse(value) as T;
        } catch {
            console.warn(`StorageProvider: failed to read key "${key}"`);
            return null;
        }
    }

    set<T>(key: string, value: T): void {
        try {
            localStorage.setItem(key, JSON.stringify(value));
        } catch (error) {
            console.error(`StorageProvider: failed to write key "${key}"`, error);
        }
    }

    remove(key: string): void {
        try {
            localStorage.removeItem(key);
        } catch {
            console.warn(`StorageProvider: failed to remove key "${key}"`);
        }
    }

    clear(): void {
        try {
            localStorage.clear();
        } catch {
            console.warn('StorageProvider: failed to clear storage');
        }
    }
}

/**
 * In-memory storage fallback for environments without localStorage
 * (e.g., private browsing, SSR, tests)
 */
export class MemoryStorageProvider implements StorageProvider {
    private storage: Map<string, string> = new Map();

    get<T>(key: string): T | null {
        const value = this.storage.get(key);
        if (value === undefined) {
            return null;
        }
        try {
            return JSON.parse(value) as T;
        } catch {
            return null;
        }
    }

    set<T>(key: string, value: T): void {
        this.storage.set(key, JSON.stringify(value));
    }

    remove(key: string): void {
        this.storage.delete(key);
    }

    clear(): void {
        this.storage.clear();
    }
}

/**
 * Check if localStorage is available
 */
function isLocalStorageAvailable(): boolean {
    try {
        const testKey = '__storage_test__';
        localStorage.setItem(testKey, testKey);
        localStorage.removeItem(testKey);
        return true;
    } catch {
        return false;
    }
}

/** Cached storage provider instance */
let cachedProvider: StorageProvider | null = null;

/**
 * Get the appropriate storage provider with graceful fallback
 * @returns LocalStorageProvider if available, otherwise MemoryStorageProvider
 */
export function getStorageProvider(): StorageProvider {
    if (cachedProvider === null) {
        cachedProvider = isLocalStorageAvailable() ? new LocalStorageProvider() : new MemoryStorageProvider();
    }
    return cachedProvider;
}

/**
 * Reset the cached provider (useful for testing)
 */
export function resetStorageProvider(): void {
    cachedProvider = null;
}
