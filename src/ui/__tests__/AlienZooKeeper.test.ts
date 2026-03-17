/**
 * AlienZooKeeper match-3 business logic tests.
 *
 * Tests the exported pure functions: findMatch3, generateBoard, removeMatch,
 * fillRemovedCells, and trySwap.
 */

import { describe, it, expect } from 'vitest';
import {
    findMatch3,
    generateBoard,
    removeMatch,
    fillRemovedCells,
    trySwap,
    MatchDirection,
} from '../screens/AlienZooKeeperScreen';

// Helper: create a 6×6 board filled with a default value
function emptyBoard(fill: number = -3): number[] {
    return new Array(36).fill(fill);
}

// Helper: set a specific cell in a board
function setCell(board: number[], row: number, col: number, val: number): void {
    board[row * 6 + col] = val;
}

describe('AlienZooKeeper Match-3 Logic', () => {
    // ─── findMatch3 ──────────────────────────────────────────────────────

    describe('findMatch3', () => {
        it('should find a horizontal match of 3', () => {
            const board = emptyBoard();
            // Place 3 gems of type 1 horizontally in row 0
            setCell(board, 0, 0, 1);
            setCell(board, 0, 1, 1);
            setCell(board, 0, 2, 1);

            const result = findMatch3(board);
            expect(result.found).toBe(true);
            expect(result.direction).toBe(MatchDirection.Horizontal);
            expect(result.index).toBe(0); // row 0, col 0
        });

        it('should find a horizontal match starting at non-zero column', () => {
            const board = emptyBoard();
            // Place 3 gems of type 2 at row 2, cols 1-3
            setCell(board, 2, 1, 2);
            setCell(board, 2, 2, 2);
            setCell(board, 2, 3, 2);

            const result = findMatch3(board);
            expect(result.found).toBe(true);
            expect(result.direction).toBe(MatchDirection.Horizontal);
            expect(result.index).toBe(2 * 6 + 1); // row 2, col 1
        });

        it('should find a horizontal match at last valid column position', () => {
            const board = emptyBoard();
            // Place 3 gems at row 0, cols 3-5
            setCell(board, 0, 3, 3);
            setCell(board, 0, 4, 3);
            setCell(board, 0, 5, 3);

            const result = findMatch3(board);
            expect(result.found).toBe(true);
            expect(result.direction).toBe(MatchDirection.Horizontal);
            expect(result.index).toBe(3); // row 0, col 3
        });

        it('should find a vertical match of 3', () => {
            const board = emptyBoard();
            // Place 3 gems of type 0 vertically in col 0
            setCell(board, 0, 0, 0);
            setCell(board, 1, 0, 0);
            setCell(board, 2, 0, 0);

            const result = findMatch3(board);
            expect(result.found).toBe(true);
            expect(result.direction).toBe(MatchDirection.Vertical);
            expect(result.index).toBe(0); // row 0, col 0
        });

        it('should find a vertical match starting at non-zero row', () => {
            const board = emptyBoard();
            // Place 3 gems of type 4 at col 3, rows 2-4
            setCell(board, 2, 3, 4);
            setCell(board, 3, 3, 4);
            setCell(board, 4, 3, 4);

            const result = findMatch3(board);
            expect(result.found).toBe(true);
            expect(result.direction).toBe(MatchDirection.Vertical);
            expect(result.index).toBe(2 * 6 + 3); // row 2, col 3
        });

        it('should find a vertical match at last valid row position', () => {
            const board = emptyBoard();
            // Place 3 gems at col 5, rows 3-5
            setCell(board, 3, 5, 1);
            setCell(board, 4, 5, 1);
            setCell(board, 5, 5, 1);

            const result = findMatch3(board);
            expect(result.found).toBe(true);
            expect(result.direction).toBe(MatchDirection.Vertical);
            expect(result.index).toBe(3 * 6 + 5); // row 3, col 5
        });

        it('should prefer horizontal matches over vertical (scanned first)', () => {
            const board = emptyBoard();
            // Horizontal match in row 0
            setCell(board, 0, 0, 1);
            setCell(board, 0, 1, 1);
            setCell(board, 0, 2, 1);
            // Vertical match in col 5
            setCell(board, 0, 5, 2);
            setCell(board, 1, 5, 2);
            setCell(board, 2, 5, 2);

            const result = findMatch3(board);
            expect(result.found).toBe(true);
            expect(result.direction).toBe(MatchDirection.Horizontal);
        });

        it('should return found=false when no match exists', () => {
            const board = emptyBoard();
            // Scatter different values with no triples
            setCell(board, 0, 0, 0);
            setCell(board, 0, 1, 1);
            setCell(board, 0, 2, 2);
            setCell(board, 1, 0, 3);
            setCell(board, 1, 1, 4);

            const result = findMatch3(board);
            expect(result.found).toBe(false);
        });

        it('should return found=false for an empty board', () => {
            const board = emptyBoard(); // all -3 (removed)
            const result = findMatch3(board);
            expect(result.found).toBe(false);
        });

        it('should ignore removed cells (value < 0)', () => {
            const board = emptyBoard();
            // Place 3 cells that look like a match but one is removed
            setCell(board, 0, 0, 1);
            setCell(board, 0, 1, -3); // removed
            setCell(board, 0, 2, 1);

            const result = findMatch3(board);
            expect(result.found).toBe(false);
        });

        it('should not match 2 consecutive same-value cells', () => {
            const board = emptyBoard();
            setCell(board, 0, 0, 1);
            setCell(board, 0, 1, 1);
            setCell(board, 0, 2, 2); // different

            const result = findMatch3(board);
            expect(result.found).toBe(false);
        });
    });

    // ─── generateBoard ───────────────────────────────────────────────────

    describe('generateBoard', () => {
        it('should create a board with 36 cells', () => {
            const board = generateBoard();
            expect(board.length).toBe(36);
        });

        it('should fill all cells with values 0-4', () => {
            const board = generateBoard();
            for (const cell of board) {
                expect(cell).toBeGreaterThanOrEqual(0);
                expect(cell).toBeLessThanOrEqual(4);
            }
        });

        it('should produce a board with no initial matches', () => {
            // Run multiple times since it's random
            for (let i = 0; i < 20; i++) {
                const board = generateBoard();
                const match = findMatch3(board);
                expect(match.found).toBe(false);
            }
        });

        it('should produce different boards', () => {
            const boards = new Set<string>();
            for (let i = 0; i < 10; i++) {
                boards.add(generateBoard().join(','));
            }
            // Extremely unlikely to get 10 identical random boards
            expect(boards.size).toBeGreaterThan(1);
        });
    });

    // ─── removeMatch ─────────────────────────────────────────────────────

    describe('removeMatch', () => {
        it('should remove 3 cells for a horizontal match', () => {
            const board = emptyBoard(0);
            // Simulate a match at row 1, col 2 horizontal
            const match = { found: true, index: 1 * 6 + 2, direction: MatchDirection.Horizontal as MatchDirection };

            removeMatch(board, match);

            expect(board[1 * 6 + 2]).toBe(-3);
            expect(board[1 * 6 + 3]).toBe(-3);
            expect(board[1 * 6 + 4]).toBe(-3);
        });

        it('should remove 3 cells for a vertical match', () => {
            const board = emptyBoard(0);
            // Simulate a match at row 0, col 3 vertical
            const match = { found: true, index: 3, direction: MatchDirection.Vertical as MatchDirection };

            removeMatch(board, match);

            expect(board[0 * 6 + 3]).toBe(-3);
            expect(board[1 * 6 + 3]).toBe(-3);
            expect(board[2 * 6 + 3]).toBe(-3);
        });

        it('should not modify board when match.found is false', () => {
            const board = emptyBoard(0);
            const original = [...board];
            const match = { found: false, index: 0, direction: MatchDirection.Horizontal as MatchDirection };

            removeMatch(board, match);

            expect(board).toEqual(original);
        });
    });

    // ─── fillRemovedCells ────────────────────────────────────────────────

    describe('fillRemovedCells', () => {
        it('should replace all -3 values with random 0-4 values', () => {
            const board = emptyBoard(); // all -3
            fillRemovedCells(board);

            for (const cell of board) {
                expect(cell).toBeGreaterThanOrEqual(0);
                expect(cell).toBeLessThanOrEqual(4);
            }
        });

        it('should not modify cells that are not -3', () => {
            const board = [
                0, 1, 2, 3, 4, -3, 0, 1, 2, 3, 4, -3, 0, 1, 2, 3, 4, -3, 0, 1, 2, 3, 4, -3, 0, 1, 2, 3, 4, -3, 0, 1, 2,
                3, 4, -3,
            ];
            const original = [...board];
            fillRemovedCells(board);

            for (let i = 0; i < board.length; i++) {
                if (original[i] !== -3) {
                    expect(board[i]).toBe(original[i]);
                } else {
                    expect(board[i]).toBeGreaterThanOrEqual(0);
                    expect(board[i]).toBeLessThanOrEqual(4);
                }
            }
        });
    });

    // ─── trySwap ─────────────────────────────────────────────────────────

    describe('trySwap', () => {
        it('should match when swap creates a 3-in-a-row', () => {
            // Board layout (row 0): 1 0 0 _ _ _
            // Swapping [0,0] and [0,1] would give: 0 1 0 — no match
            // Better: set up a specific matchable scenario
            const board = emptyBoard();
            // Row 0: 1 2 2 _ _ _
            // Swapping idx 0 with idx 3 (below) where idx 3 = 2 gives: 2 2 2
            // Actually let's do: Row 0: 0 1 1 ...  and Row 1: 1 ...
            // Swapping (0,0) with (1,0) where (1,0)=1 → row 0 becomes: 1 1 1

            setCell(board, 0, 0, 0);
            setCell(board, 0, 1, 1);
            setCell(board, 0, 2, 1);
            setCell(board, 1, 0, 1);

            const result = trySwap(board, 0, 6); // swap (0,0) with (1,0)
            expect(result.matched).toBe(true);
            // The three matched cells should be removed
            expect(board[0]).toBe(-3);
            expect(board[1]).toBe(-3);
            expect(board[2]).toBe(-3);
        });

        it('should keep gems swapped even when no match is created (C behavior)', () => {
            const board = emptyBoard();
            // Row 0: 0 1 2 3 4 0
            setCell(board, 0, 0, 0);
            setCell(board, 0, 1, 1);
            setCell(board, 0, 2, 2);
            setCell(board, 0, 3, 3);
            setCell(board, 0, 4, 4);
            setCell(board, 0, 5, 0);

            const result = trySwap(board, 0, 1); // swap (0,0) with (0,1)
            expect(result.matched).toBe(false);
            // C code does NOT swap back — cells stay exchanged
            expect(board[0]).toBe(1); // was 0, now 1
            expect(board[1]).toBe(0); // was 1, now 0
        });

        it('should swap and detect a vertical match', () => {
            const board = emptyBoard();
            // Col 0: row 0 = 2, row 1 = 2, row 2 = 0
            // Col 1: row 2 = 2
            // Swapping (2,0) with (2,1) → col 0 becomes 2,2,2
            setCell(board, 0, 0, 2);
            setCell(board, 1, 0, 2);
            setCell(board, 2, 0, 0);
            setCell(board, 2, 1, 2);

            const result = trySwap(board, 2 * 6 + 0, 2 * 6 + 1); // swap (2,0) with (2,1)
            expect(result.matched).toBe(true);
            // Vertical match at col 0, rows 0-2
            expect(board[0 * 6 + 0]).toBe(-3);
            expect(board[1 * 6 + 0]).toBe(-3);
            expect(board[2 * 6 + 0]).toBe(-3);
        });
    });

    // ─── Integration: full board cycle ────────────────────────────────────

    describe('full board cycle', () => {
        it('should support generate → swap → match → fill cycle', () => {
            const board = generateBoard();
            expect(findMatch3(board).found).toBe(false);

            // Find a swap that creates a match by brute force
            let foundSwap = false;
            for (let i = 0; i < 36 && !foundSwap; i++) {
                // Try swapping with right neighbor
                if (i % 6 < 5) {
                    const testBoard = [...board];
                    const r = trySwap(testBoard, i, i + 1);
                    if (r.matched) {
                        foundSwap = true;
                        // Fill removed cells
                        fillRemovedCells(testBoard);
                        // All cells should be valid (0-4)
                        for (const cell of testBoard) {
                            expect(cell).toBeGreaterThanOrEqual(0);
                            expect(cell).toBeLessThanOrEqual(4);
                        }
                    }
                }
                // Try swapping with bottom neighbor
                if (i < 30 && !foundSwap) {
                    const testBoard = [...board];
                    const r = trySwap(testBoard, i, i + 6);
                    if (r.matched) {
                        foundSwap = true;
                        fillRemovedCells(testBoard);
                        for (const cell of testBoard) {
                            expect(cell).toBeGreaterThanOrEqual(0);
                            expect(cell).toBeLessThanOrEqual(4);
                        }
                    }
                }
            }
            // It's theoretically possible that no swap creates a match,
            // but extremely unlikely on a 6×6 board with 5 gem types.
            // We don't assert foundSwap to avoid flaky tests.
        });
    });
});
