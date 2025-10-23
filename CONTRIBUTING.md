# Contributing to OpenPdfGuard

Thank you for your interest in contributing to **OpenPdfGuard**!  
This project provides a lightweight C++ library and CLI for converting files to PDF, adding watermarks, and encrypting PDFs.

We welcome all kinds of contributions: bug fixes, feature enhancements, documentation improvements, and tests.
## Getting Started
- Check the **TODO** file in the repository — it lists tasks, features, and improvements that could use contributions.  
- Pick something that interests you and matches your skill level.
- If the change is significant, open an issue first to discuss it.
- Include compiler extra warnings and fix what is reported by the compiler.
- Occasionally run `make cppcheck` and `make cpplint` and fix what is reported. These tool can give false positives especially around header files so use your judgement or ask for help in Discussions page.

## Pull Requests
- Pull requests are welcome.  
- For major changes, please open an issue first to discuss your proposed changes.
- Keep commits clear and focused; describe what and why you changed something.
## Tests

- Please add or update tests as appropriate when contributing new functionality.
- Unit tests are located in the `tests/` folder.

---

## Code Style & Quality

- Use **snake_case** for classes, variables and functions.
- Follow the existing C++ conventions in the codebase.
- Format code using **Google C++ Style** (e.g., `clang-format`).
