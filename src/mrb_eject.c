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
  mrb_value arg = mrb_nil_value();

  mrb_get_args(mrb, "|o", &arg);

#ifdef _WIN32
  if (mrb_nil_p(arg)) {
    if (mciSendString("capability cdaudio can eject", NULL, 0, NULL) == 0)
      arg = mrb_true_value();
  }
  if (mrb_type(arg) == MRB_TT_TRUE)
    mciSendString("set cdaudio door open", NULL, 0, NULL);
  else
    mciSendString("set cdaudio door closed", NULL, 0, NULL);
#else
  int fd = open("/dev/cdrom", O_RDONLY | O_NONBLOCK);
  if (fd == -1) {
    perror("open");
  } else {
    int e = CDROMEJECT;
    if (mrb_nil_p(arg)) {
      if (ioctl(fd, CDROM_DRIVE_STATUS, 0) == CDS_TRAY_OPEN)
        e = CDROMCLOSETRAY;
    } else if (mrb_type(arg) == MRB_TT_TRUE)
      e = CDROMEJECT;
    else
      e = CDROMCLOSETRAY;
    if (ioctl(fd, e, 0) < 0)
      perror("ioctl");
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
