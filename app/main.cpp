#include <podofo/podofo.h>

#include "font_params.h"
#include "pdf_guard.h"
using namespace opg;
int main() {
  pdf_opt opt =
      pdf_opt::builder()
          .set_watermark(font_params::builder().set_text("test test").build())
          .build();

  pdf_guard gueard;
  gueard.convert_file("/home/samuil/Downloads/1748955209584.jpg", "output.pdf",
                      opt);

  return 0;
}