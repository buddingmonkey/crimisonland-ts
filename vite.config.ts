import { defineConfig } from 'vitest/config';
import { resolve } from 'path';

export default defineConfig({
    base: process.env.VITE_BASE || '/',
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
                manualChunks(id: string) {
                    if (id.includes('node_modules/pixi')) return 'pixi';
                    if (id.includes('node_modules/pako')) return 'vendor';
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
    },
});
