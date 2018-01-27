# Framebot - Alpha [![Build Status](https://travis-ci.org/giancarlopro/Telebot-TelegramBotAPI.svg?branch=master)](https://travis-ci.org/giancarlopro/Telebot-TelegramBotAPI)

This is the official repository for Framebot.

## Building from source

First you need to install the dependencies

```
apt install jansson openssl libcurl4-openssl-dev
```

then you use cmake to create the build files
```
mkdir build
cd build
cmake ..
```

and use make to build and install
```
make
make install
```

## Usage
```C
#include <telebot.h>
#define TOKEN "123456:ABC-DEF1234ghIkl-zyx57W2v1u123ew11"
...
int main () {
  telebot_init ();
  Bot *frame_bot = telebot(TOKEN);
  send_message_chat(frame_bot, chat_id, "Message", NULL, false, false, 0, NULL);
  ...
  bot_free(frame_bot);
  return 0;
}
```

## Contributing

If you want to contribute to the project, follow the instructions on [CONTRIBUTING](CONTRIBUTING.md)
