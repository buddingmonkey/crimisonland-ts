---
description: Implement a C code feature completely with integration and tracker updates
---

# Feature Implementation Workflow

This workflow implements a C code feature from start to finish, including integration and documentation.

## Prerequisites
- Feature name/description from user
- C code line references (if available)
- Target system/file location

## Steps

### 1. Research & Planning
- Locate the C code implementation in `crimsonland.exe_decompiled.c`
- Identify exact line numbers and function boundaries
- Document dependencies and related systems
- Create implementation plan artifact with:
  - C code references (exact line numbers)
  - Proposed TypeScript structure
  - Integration points
  - Verification plan

### 2. Implementation
- Create new files or modify existing files as needed
- Port C code function-by-function with exact line references in comments
- Follow existing code patterns and naming conventions
- Use TypeScript types and interfaces appropriately
- Add JSDoc comments with C line references

### 3. Integration
- Identify all systems that need to use the new feature
- Update relevant files to import and use the new implementation
- Ensure proper data flow between systems
- Fix any TypeScript errors or linting issues
- Replace any hex constants with proper enum values

### 4. Verification
- Check that all TypeScript errors are resolved
- Verify the implementation matches C code behavior
- Test integration points (if possible)
- Document any deviations from C code with justification

### 5. Documentation Updates
- Update `C_CODE_PORTING_TRACKER.md`:
  - Add feature to appropriate section
  - Include exact C line references
  - Mark status as "✅ Complete + Integrated"
  - Update summary statistics if needed
- Create or update walkthrough artifact documenting:
  - What was implemented
  - Where it was integrated
  - C code references
  - Any important design decisions

### 6. Completion Report
- Provide concise summary of:
  - Files created/modified
  - Lines of code ported
  - Integration points
  - Tracker updates made

## Example Usage

User: "Implement the poison damage system"

Agent will:
1. Find poison damage code in C (e.g., lines 15000-15200)
2. Create `PoisonSystem.ts` with exact C code port
3. Integrate into `CollisionSystem.ts` and `Enemy.ts`
4. Fix all TypeScript errors
5. Update tracker with poison system entry
6. Create walkthrough documenting the implementation

## Notes
- Always include exact C line references in code comments
- Mark features as "Complete + Integrated" only when fully working
- Keep tracker updates synchronized with actual implementation status
- Use PerkId/enum values instead of hex constants
- Follow the existing code organization patterns
