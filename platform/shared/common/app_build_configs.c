// WARNING! THIS FILE IS GENERATED AUTOMATICALLY! DO NOT EDIT IT MANUALLY!

#include <string.h>

#include "app_build_configs.h"

static const char* keys[] = { ""
,"name"
};

static const char* values[] = { ""
,"EmbeddedJSVM"
};

#define APP_BUILD_CONFIG_COUNT 2

const char* get_app_build_config_item(const char* key) {
  int i;
  for (i = 1; i < APP_BUILD_CONFIG_COUNT; i++) {
    if (strcmp(key, keys[i]) == 0) {
      return values[i];
    }
  }
  return 0;
}

