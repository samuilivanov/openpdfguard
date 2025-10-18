# OpenPdfGuard

OpenPdfGuard is a c++ library and application that converts files to PDF format, can add watermarks, and encrypts PDF files.

## Compiling

```bash
git clone https://github.com/yourname/OpenPdfGuard.git
cd openpdfguard
mkdir build && cd build
cmake ..
make -j$(nproc)
```
## Usage CLI

```bash
openpdfguard input.docx
=== OpenPdfGuard ===
Input: input.docx
Add watermark? [y/N]: y
Watermark text (CONFIDENTIAL): test
Font (Helvetica): Arial
Font size (24): 50
Rotation degrees (0): 40
Image path (leave empty for text): 
Adding watermark: 'test' font=Arial size=50 rot=40 ... done.
Encrypt PDF? [y/N]: n

All tasks completed successfully.
Output file: input.pdf
```

## Usage as library

```cpp
int main() {
  opg::pdf_guard guard;
  opg::font_params params =
      opg::font_params::builder().set_text("Test").build();
  opg::pdf_opt opt = opg::pdf_opt::builder().set_watermark(params).build();
  guard.convert_file("path_to_file", "path_for_output", opt);
}
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

This software is distributed under the GNU General Public License v2 or later.

This software links to the LibreOffice UNO Runtime Libraries,
which are licensed under the Mozilla Public License v2.0.