# undr
*Personal C library with multiple utilities. The name undr provides from a short story by Jorge Luis Borges*

## Caveats
- This library has been developed on and for Linux following open source philosophy.
- Dependencies: `openssl`
- This library is available in AUR repositories (Arch Linux)

## Utilities
- Format and prettify JSON, XML and HTML strings
- Arena allocator
- JWT decoder

## Usage
#### Format JSON, XML or HTML
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <undr/format.h>

int main() {
  const char* json_input = "{\"a\":1,\"b\":[1,2]}";
  char* json = format_json(json_input, 2, 5);
  printf("formatted json:\n %s\n", json);

  const char* xml_input = "<?xml version=\"1.0\"?><root><user><name>John</name><id>1</id></user></root>";
  char* xml = format_xml(xml_input, 2, 5);
  printf("formatted xml:\n %s\n", xml);

  return 0;
}
```

#### Arena
```c
#include <string.h>
#include <stdlib.h>
#include <undr/arena.h>

int main() {
  Arena *arena = arena_init(1024);

  int *numbers = arena_alloc(arena, 5 * sizeof(int));
  for (int i = 0; i < 5; i++) numbers[i] = i * 10;

  char *msg = arena_alloc(arena, 20);
  strcpy(msg, "Hello Arena!");

  arena_free(arena);

  return 0;
}
```

#### JWT decoder
```c
#include <string.h>
#include <stdlib.h>
#include <undr/jwt.h>

int main() {
  Arena *arena = arena_init(1024);

  const char *raw_jwt =
        "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9."
        "eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MD"
        "IyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c";

  Jwt token = decode_jwt(arena, raw_jwt);

  if (token.header && token.payload) {
    printf("Header:\n %s\n", token.header);
    printf("Payload:\n %s\n", token.payload);
  }

  arena_free(arena);

  return 0;
}
```

---

### Donate
- **Bitcoin** [(QR)](https://raw.githubusercontent.com/javiorfo/img/master/crypto/bitcoin.png)  `1GqdJ63RDPE4eJKujHi166FAyigvHu5R7v`
- [Paypal](https://www.paypal.com/donate/?hosted_button_id=FA7SGLSCT2H8G)

