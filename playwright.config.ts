import { defineConfig, devices } from '@playwright/test';

export default defineConfig({
    testDir: './e2e',
    fullyParallel: false, // Run tests sequentially — they share a game server
    retries: 0,
    timeout: 30_000,
    expect: {
        timeout: 10_000,
    },
    use: {
        baseURL: 'http://localhost:5173',
        // Keep headed false for CI; use --headed flag for local debugging
        headless: true,
        screenshot: 'only-on-failure',
        video: 'retain-on-failure',
    },
    projects: [
        {
            name: 'chromium',
            use: { ...devices['Desktop Chrome'] },
        },
    ],
    webServer: {
        command: 'npm run dev',
        url: 'http://localhost:5173',
        reuseExistingServer: !process.env.CI,
        timeout: 15_000,
    },
});
