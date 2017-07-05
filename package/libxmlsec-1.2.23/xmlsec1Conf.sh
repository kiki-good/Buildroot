#
# Configuration file for using the XML library in GNOME applications
#
prefix="/usr"
exec_prefix="/usr"
libdir="${exec_prefix}/lib"
includedir="${prefix}/include"

XMLSEC_LIBDIR="${exec_prefix}/lib"
XMLSEC_INCLUDEDIR=" -D__XMLSEC_FUNCTION__=__func__ -DXMLSEC_NO_SIZE_T -DXMLSEC_NO_GOST=1 -DXMLSEC_NO_GOST2012=1 -DXMLSEC_NO_CRYPTO_DYNAMIC_LOADING=1 -I${prefix}/include/xmlsec1   -I/home/jqiao/spk_64bit/spk/objOutput/bskyb-brcm64bit/build_aarch64/staging_dir/usr/include/libxml2   -I/home/jqiao/spk_64bit/spk/objOutput/bskyb-brcm64bit/build_aarch64/staging_dir/usr/include/libxml2   -I/home/jqiao/spk_64bit/spk/objOutput/bskyb-brcm64bit/build_aarch64/staging_dir/home/jqiao/spk_64bit/spk/objOutput/bskyb-brcm64bit/build_aarch64/staging_dir/usr/include   -DXMLSEC_OPENSSL_110=1 -DXMLSEC_CRYPTO_OPENSSL=1"
XMLSEC_LIBS="-L${exec_prefix}/lib -lxmlsec1-openssl -lxmlsec1   -lxml2   -L/home/jqiao/spk_64bit/spk/objOutput/bskyb-brcm64bit/build_aarch64/staging_dir/home/jqiao/spk_64bit/spk/objOutput/bskyb-brcm64bit/build_aarch64/staging_dir/usr/lib -L/home/jqiao/spk_64bit/spk/objOutput/bskyb-brcm64bit/build_aarch64/staging_dir/home/jqiao/spk_64bit/spk/objOutput/bskyb-brcm64bit/build_aarch64/staging_dir/lib -lxslt -lz -liconv -ldl -lm -lxml2   -L/home/jqiao/spk_64bit/spk/objOutput/bskyb-brcm64bit/build_aarch64/staging_dir/home/jqiao/spk_64bit/spk/objOutput/bskyb-brcm64bit/build_aarch64/staging_dir/usr/lib -lssl -lcrypto  "
MODULE_VERSION="xmlsec-1.2.23-openssl"

