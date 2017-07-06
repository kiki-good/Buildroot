ifeq ($(BR2_TARGET_SKY),y)
SKY_DL_DIR=sky
include package/sky/*/*.mk
endif
