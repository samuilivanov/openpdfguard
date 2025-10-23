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

### Converting Files to PDF

Convert Word, LibreOffice, or image files to PDF format.

`./openpdfguard -i /path/to/input.docx -o /path/to/output/ convert`

Example output:
```bash
./openpdfguard -i /home/user/file-sample_100kB.doc -o /home/user/ convert
[convert] input: "/home/user/file-sample_100kB.doc" -> output dir: "/home/user/"
file:///home/home/user/file-sample_100kB.doc
file:///home/home/user/file-sample_100kB.pdf
```
### Supported formats:
```
Word/Office: .doc, .docx, .odt
Presentations: .ppt, .pptx, .odp
Spreadsheets: .xls, .xlsx, .ods
Images: .jpg, .png, .tiff, .bmp
```

### Applying Watermarks to PDFs

Add text or image watermarks to existing PDFs.
```bash
./openpdfguard -i /path/to/input.pdf -o /path/to/output/ watermark \
  --text "CONFIDENTIAL" \
  --font "Helvetica" \
  --size 48 \
  --rotation 30
```
Example output:
```
./openpdfguard -i path/to/input.pdf -o /home/samuil/Downloads/ watermark -t "TEST"
[watermark] text: 'TEST', font: Helvetica, size: 12, rotation: 45
```
### Encrypting PDFs

Encrypt PDFs with user and owner passwords.
```
./openpdfguard -i /path/to/input.pdf -o /path/to/output/ encrypt \
  --user-password "view123" \
  --owner-password "admin456"
```

### Chaining Operations

You can chain operations manually in sequence:
```
./openpdfguard -i /path/to/contract.docx -o /path/to/output/ convert
./openpdfguard -i /path/to/output/contract.pdf -o /path/to/output/ watermark \
  --text "TOP SECRET" --font "Arial" --size 42 --rotation 45
./openpdfguard -i /path/to/output/contract_watermarked.pdf -o /path/to/output/ encrypt \
  --user-password "readonly" --owner-password "fullaccess"
```
#### Notes
-i (input) and -o (output) must always come before the subcommand.

Each subcommand (convert, watermark, encrypt) can be run independently.

Output PDFs are placed in the directory specified by -o.

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