KERNEL_FILE = "kernel.itb"
ROOTFS_FILE = "rootfs.tar.bz2"

# Amlogic defaults
require conf/machine/include/arm/arch-armv8.inc
require conf/machine/include/soc-family.inc

IMAGE_CLASSES += "sdcard_image-alien5"
SDCARD_ROOTFS ?= "${DEPLOY_DIR_IMAGE}/${IMAGE_NAME}.rootfs.ext4"
IMAGE_FSTYPES ?= "ext4 alien5sdimg"
#IMAGE_ROOTFS_SIZE = "976562"
IMAGE_ROOTFS_SIZE = "476562"
IMAGE_EXTRA_SPACE = "0"
IMAGE_OVERHEAD_FACTOR = "1.0"

BB_HASH_IGNORE_MISMATCH = "1"

# Serial console to be used
SERIAL_CONSOLE = "115200 ttyS0"

KERNEL_CLASSES += "aarch64-fitimage"
KERNEL_IMAGETYPE = "fitImage"

UBOOT_ENTRYPOINT = "0x01080000"
UBOOT_LOADADDRESS = "0x01080000"

#INITRAMFS_IMAGE = "linkdroid-initramfs"

MACHINE_FEATURES = "bluetooth usbhost vfat alsa dvb-c nolcd hdmicec fb skins1080 emmc aml-plugins"
#MACHINE_FEATURES = "kodi"

DVBPROVIDER = "kernel"
DVBSKYPROVIDER = "kernel"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
    linkdroid-autoscript \
    \
    linkdroid-mali-alien5 \
    linkdroid-gst-amlavsink1 \
    gst-app \
    linkdroid-libamplayer-alien5 \
    linkdroid-libamavutils-alien5 \
    linkdroid-libamadec-alien5 \
    linkdroid-libamcodec-alien5 \
    linkdroid-amlsetfb \
    \
    kernel-modules \
    amremote \
    linkdroid-opengl-amlogic \
    \
    linkdroid-stb-alien5 \
    linkdroid-libavlib-audio-so-alien5 \
    libmad \
    linkdroid-extra-alien5 \
    "

## TODO:     8189es builitin with cfg80211
MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS += "\
     \
    kernel-module-cdfs \
    kernel-module-sysfillrect \
    kernel-module-syscopyarea \
    kernel-module-mceusb \
    kernel-module-rc-core \
    kernel-module-CH341 \
    kernel-module-rfcomm \
    kernel-module-hidp \
    kernel-module-bluetooth \
    kernel-module-6lowpan-iphc \
    kernel-module-libcrc32c \
    kernel-module-xfs \
    kernel-module-8189es \
    kernel-module-cfg80211 \
    "

MACHINE_EXTRA_RRECOMMENDS += "\
    libdvbcsa \
    "

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += " ${@bb.utils.contains('MACHINE_FEATURES', 'fb', 'linkdroid-amlsetfb', '', d)}"

PREFERRED_PROVIDER_virtual/libgles1 = "linkdroid-opengl-amlogic"
PREFERRED_PROVIDER_virtual/libgles2 = "linkdroid-opengl-amlogic"
PREFERRED_PROVIDER_virtual/egl = "linkdroid-opengl-amlogic"

PREFERRED_PROVIDER_jpeg = "libjpeg-turbo"
PREFERRED_PROVIDER_jpeg-native = "libjpeg-turbo-native"

EXTRA_OECONF_append_pn-enigma2 = " --with-alsa --with-alsacard=hw:0 --with-alsamixer=Master --with-fbdev=/dev/fb0 --with-lcddev=/dev/null --with-amlogic"
DEPENDS_append_pn-enigma2 = " libdvbcsa linkdroid-libamcodec-alien5 linkdroid-libamadec-alien5 "
EXTRA_OECONF_append_pn-tuxtxt-enigma2 = " --with-fbdev=/dev/fb0"
CC_append_pn-showiframe = " -DHAVE_AMLOGIC -I${STAGING_INCDIR}/amlogic/amcodec -lamcodec"
DEPENDS_append_pn-showiframe = " linkdroid-libamcodec-alien5"

DISTRO_FEATURES_remove = "x11 wayland"

IMAGEDIR ?= "${MACHINE}"

IMAGE_CMD_alien5sdimg_append = " \
    mkdir -p ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}; \
    mv ${DEPLOY_DIR_IMAGE}/${IMAGE_NAME}-sd.img ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${IMAGE_NAME}-sd.img; \
    echo ${DISTRO_NAME}-${DISTRO_VERSION}.${BUILD_VERSION} > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/imageversion; \
    cd ${DEPLOY_DIR_IMAGE}; \
    zip ${IMAGE_NAME}_sdcard.zip ${IMAGEDIR}/*; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.ext4; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.manifest; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.json; \
    rm -f ${DEPLOY_DIR_IMAGE}/*-sd.img; \
    rm -Rf ${IMAGEDIR}; \
    "

# We know about rtc
include conf/machine/include/build-extras.inc