#include <podofo/podofo.h>

#include "watermark.h"
using namespace opg;
int main() {
  watermark mark = watermark::builder()
                       .set_text("TEST")
                       .set_rotation(45)
                       .set_transparency(0.2)
                       .build();

  mark.add_text_watermark("/home/samuil/Downloads/Invoice_56683429.pdf",
                          "output.pdf");
  mark.add_text_watermark("/home/samuil/Downloads/Invoice_56683429.pdf",
                          "output.pdf");
  mark.add_text_watermark("/home/samuil/Downloads/Invoice_56683429.pdf",
                          "output.pdf");
  return 0;
}