#include <stdio.h>
#include <string.h>
#include <mysql.h>
#include "mruby.h"
#include "mruby/compile.h"
#include "mruby/string.h"

extern "C" {

  my_bool
  mrb_eval_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
  {
    if (args->arg_count != 1) {
      strcpy(message, "`mrb_eval()` accepts just one argument.");
      return 1;
    }

    if (args->arg_type[0] != STRING_RESULT) {
      strcpy(message, "`mrb_eval()` only accepts a string value.");
      return 1;
    }

    return 0;
  }

  char *
  mrb_eval(UDF_INIT *initid, UDF_ARGS* args, char *result_buf, unsigned long *res_length, char *null_value, char *error)
  {
    mrb_state* mrb;
    mrb_value value;
    char *result;

    mrb = mrb_open();

    value = mrb_load_string(mrb, args->args[0]);
    result = (char *)mrb_string_value_ptr(mrb, value);

    strcpy(result_buf, result);
    *res_length = strlen(result);

    mrb_close(mrb);

    return result_buf;
  }

}
