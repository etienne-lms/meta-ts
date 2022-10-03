DEPENDS += "openssl-native"

export OPENSSL_MODULES="${STAGING_LIBDIR_NATIVE}/ossl-modules"
export OPENSSL_ENGINES="${STAGING_LIBDIR_NATIVE}/engines-3"
export OPENSSL_CONF="${STAGING_LIBDIR_NATIVE}/ssl-3/openssl.cnf"
export SSL_CERT_DIR="${STAGING_LIBDIR_NATIVE}/ssl-3/certs"
export SSL_CERT_FILE="${STAGING_LIBDIR_NATIVE}/ssl-3/cert.pem"
