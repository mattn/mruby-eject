#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#else
#include <fcntl.h>
#include <linux/cdrom.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#include "mruby.h"
#include <stdio.h>

mrb_value
mrb_eject(mrb_state *mrb, mrb_value klass)
{
#ifdef _WIN32
  mciSendString("set cdaudio door open", NULL, 0, NULL);
#else
  int fd = open("/dev/cdrom", O_RDONLY | O_NONBLOCK);
  if (fd != -1) {
  }
  if (fd == -1) {
    perror("open");
  } else if (ioctl(fd, CDROMEJECT, 0) < 0) {
    perror("ioctl");
  } else {
    close(fd);
  }
#endif
  return mrb_nil_value();
}

void
mrb_mruby_eject_gem_init(mrb_state* mrb) {
  mrb_define_method(mrb, mrb->kernel_module, "eject", mrb_eject, ARGS_NONE());
}

/* vim:set et ts=2 sts=2 sw=2 tw=0: */
