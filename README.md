# undr
*Personal C library with multiple utilities*

## Caveats
- This library has been developed on and for Linux following open source philosophy.
- Dependencies: `openssl`

## Utilities
- Format and prettify JSON, XML and HTML strings
- Arena allocator
- JWT decoder

## Usage
#### Formatting
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <undr/format.h>

int main() {
  const char* json_input = "{\"a\":1,\"b\":[1,2]}";
  char* json = format_json(json_input, 2, 5);
  printf("formatted json: %s", json);

  const char* xml_input = "<?xml version=\"1.0\"?><root><user><name>John</name><id>1</id></user></root>";
  char* xml = format_xml(xml_input, 2, 5);
  printf("formatted xml: %s", xml);

  return 0;
}
```

---

### Donate
- **Bitcoin** [(QR)](https://raw.githubusercontent.com/javiorfo/img/master/crypto/bitcoin.png)  `1GqdJ63RDPE4eJKujHi166FAyigvHu5R7v`
- [Paypal](https://www.paypal.com/donate/?hosted_button_id=FA7SGLSCT2H8G)

