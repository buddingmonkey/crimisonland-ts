/**
 * FullscreenButton - HTML overlay button for toggling browser fullscreen mode.
 *
 * Positioned in the bottom-right corner of the game canvas.
 * Shown only when the main menu or pause menu is visible.
 */

// SVG icons for expand (enter fullscreen) and compress (exit fullscreen)
const EXPAND_SVG = `<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" width="20" height="20">
  <polyline points="15 3 21 3 21 9"></polyline>
  <polyline points="9 21 3 21 3 15"></polyline>
  <line x1="21" y1="3" x2="14" y2="10"></line>
  <line x1="3" y1="21" x2="10" y2="14"></line>
</svg>`;

const COMPRESS_SVG = `<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" width="20" height="20">
  <polyline points="4 14 10 14 10 20"></polyline>
  <polyline points="20 10 14 10 14 4"></polyline>
  <line x1="14" y1="10" x2="21" y2="3"></line>
  <line x1="3" y1="21" x2="10" y2="14"></line>
</svg>`;

export class FullscreenButton {
    private button: HTMLButtonElement;
    private isFullscreen: boolean = false;

    constructor() {
        this.button = document.createElement('button');
        this.button.id = 'fullscreen-btn';
        this.button.innerHTML = EXPAND_SVG;
        this.button.title = 'Toggle fullscreen';

        // Style the button
        Object.assign(this.button.style, {
            position: 'absolute',
            zIndex: '100',
            display: 'none', // Hidden by default
            alignItems: 'center',
            justifyContent: 'center',
            width: '36px',
            height: '36px',
            padding: '0',
            border: '1px solid rgba(255, 255, 255, 0.15)',
            borderRadius: '6px',
            background: 'rgba(0, 0, 0, 0.5)',
            color: 'rgba(255, 255, 255, 0.7)',
            cursor: 'pointer',
            transition: 'background 0.2s, color 0.2s, border-color 0.2s',
            outline: 'none',
            pointerEvents: 'auto',
        });

        // Hover effects
        this.button.addEventListener('mouseenter', () => {
            this.button.style.background = 'rgba(0, 0, 0, 0.75)';
            this.button.style.color = 'rgba(255, 255, 255, 1)';
            this.button.style.borderColor = 'rgba(255, 255, 255, 0.35)';
        });
        this.button.addEventListener('mouseleave', () => {
            this.button.style.background = 'rgba(0, 0, 0, 0.5)';
            this.button.style.color = 'rgba(255, 255, 255, 0.7)';
            this.button.style.borderColor = 'rgba(255, 255, 255, 0.15)';
        });

        // Click handler — toggle fullscreen
        this.button.addEventListener('click', (e) => {
            e.preventDefault();
            e.stopPropagation();
            this.toggleFullscreen();
        });

        // Listen for fullscreen changes (e.g., user presses Escape to exit)
        document.addEventListener('fullscreenchange', () => {
            this.isFullscreen = !!document.fullscreenElement;
            this.button.innerHTML = this.isFullscreen ? COMPRESS_SVG : EXPAND_SVG;
        });

        document.body.appendChild(this.button);
    }

    /** Toggle browser fullscreen mode */
    private toggleFullscreen(): void {
        if (document.fullscreenElement) {
            document.exitFullscreen().catch(() => { });
        } else {
            document.documentElement.requestFullscreen().catch(() => { });
        }
    }

    /**
     * Update the button position to stay anchored to the bottom-right of the canvas.
     * Called by PixiGrimAdapter.handleResize().
     */
    updatePosition(canvasLeft: number, canvasTop: number, canvasWidth: number, canvasHeight: number): void {
        const margin = 8;
        this.button.style.left = `${canvasLeft + canvasWidth - 36 - margin}px`;
        this.button.style.top = `${canvasTop + canvasHeight - 36 - margin}px`;
    }

    /** Show the button (used when main menu or pause menu is visible) */
    show(): void {
        this.button.style.display = 'flex';
    }

    /** Hide the button (used during gameplay) */
    hide(): void {
        this.button.style.display = 'none';
    }

    /** Clean up the DOM element */
    destroy(): void {
        this.button.remove();
    }
}
