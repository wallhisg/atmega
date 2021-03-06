LOCAL_BASE	:= src
LOCAL_MDLS	:= driver/gpio driver/uart driver/timer
LOCAL_BLDS	:= $(addprefix $(LOCAL_BASE)/, $(LOCAL_MDLS))
LOCAL_INCS	:= $(wildcard $(INCLUDE_DIRS)/$(LOCAL_MDLS)/*.h)

LOCAL_SRCS	:= $(wildcard $(LOCAL_BASE)/*.c)
LOCAL_SRCS	+= $(foreach sdir, $(LOCAL_BLDS), $(wildcard $(sdir)/*.c))

LOCAL_OBJS	:= $(patsubst %.c, %.o, $(LOCAL_SRCS))
LOCAL_DEPS	:= $(patsubst %.c, %.deps, $(LOCAL_SRCS))

SRCS		+= $(LOCAL_SRCS)
OBJS		+= $(LOCAL_OBJS)
DEPS		+= $(LOCAL_DEPS)

$(LOCAL_DEPS): $(LOCAL_SRCS) $(LOCAL_INCS)
	@$(CC) -MM $< > $@

$(LOCAL_OBJS): $(LOCAL_SRCS) $(LOCAL_DEPS)
