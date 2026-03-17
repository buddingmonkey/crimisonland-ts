/**
 * Crimsonland TypeScript - Main Entry Point
 *
 * Startup flow:
 * 1. Try to detect if PAQ files are served by the dev server (Vite)
 * 2. If not available, check IndexedDB for cached PAQ files
 * 3. If not cached, show upload screen and store in IndexedDB
 * 4. Initialize and start the game
 */

import { Game, GameState } from './Game';
import { gameConsole } from './console/Console';
import { hasStoredAssets, getStoredAsset, storeAsset } from './data/AssetStorage';
import { showUploadScreen } from './ui/screens/AssetUploadScreen';

/**
 * Check if PAQ files are available via the dev server (Vite).
 * Uses a HEAD request to avoid downloading the full file.
 */
async function hasDevServerAssets(): Promise<boolean> {
    try {
        const response = await fetch('/content/crimson.paq', { method: 'HEAD' });
        return response.ok;
    } catch {
        return false;
    }
}

async function main() {
    console.log('Starting Crimsonland TypeScript...');

    let preloadedAssets: { crimsonPaq: ArrayBuffer; sfxPaq: ArrayBuffer } | undefined;

    // Check if PAQ files are served by the dev server
    const devMode = await hasDevServerAssets();

    if (!devMode) {
        // Production mode — need PAQ files from IndexedDB or upload
        const hasAssets = await hasStoredAssets();

        if (hasAssets) {
            console.log('Loading assets from IndexedDB...');
            const crimsonPaq = await getStoredAsset('crimson.paq');
            const sfxPaq = await getStoredAsset('sfx.paq');

            if (crimsonPaq && sfxPaq) {
                preloadedAssets = { crimsonPaq, sfxPaq };
            }
        }

        if (!preloadedAssets) {
            // Show upload screen and wait for user to provide files
            console.log('Showing asset upload screen...');
            const files = await showUploadScreen();

            // Store in IndexedDB for next time
            await storeAsset('crimson.paq', files.crimsonPaq);
            await storeAsset('sfx.paq', files.sfxPaq);
            console.log('Assets stored in IndexedDB');

            preloadedAssets = files;
        }
    }

    const game = new Game(preloadedAssets);

    // Expose game bridge for Playwright E2E tests
    (window as any).__CRIMSON__ = {
        game,
        console: gameConsole,
        GameState,
    };

    const success = await game.init();
    if (!success) {
        console.error('Failed to initialize game');
        return;
    }

    game.start();
}

main().catch(console.error);
