#!/bin/bash

if [[ -f configure-done ]]; then
    echo "Skipping configure step, already done."
else
    ./configure --prefix=${PREFIX} \
        --oldincludedir=${BUILD_PREFIX}/${HOST}/sysroot/usr/include \
        --enable-shared
fi

touch configure-done

make -j${CPU_COUNT} install