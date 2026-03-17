import { defineConfig } from 'vite';
import type { UserConfig } from 'vitest/config';
import { resolve } from 'path';

export default defineConfig({
    resolve: {
        alias: {
            '@': resolve(__dirname, './src'),
        },
    },
    server: {
        port: 5173,
        open: true,
    },
    build: {
        target: 'esnext',
        outDir: 'dist',
        chunkSizeWarningLimit: 900,
        rollupOptions: {
            output: {
                manualChunks: {
                    pixi: ['pixi.js'],
                    vendor: ['pako'],
                },
            },
        },
    },
    test: {
        coverage: {
            provider: 'v8',
            reporter: ['text', 'html', 'lcov'],
            include: ['src/**/*.ts'],
            exclude: ['src/**/__tests__/**', 'src/**/*.test.ts'],
        },
    } satisfies UserConfig['test'],
});
