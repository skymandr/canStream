FROM ubuntu:15.10

# Install dependencies for Kvaser CANlib:
RUN apt-get update && apt-get install -y \
    wget \
    build-essential \
    linux-headers-`uname -r` \
    --no-install-recommends && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Install Kvaser CANlib:
RUN wget http://www.kvaser.com/software/7330130980754/V5_13_0/linuxcan.tar.gz && \
    tar -xzf linuxcan.tar.gz && \
    # Remove timestamps from files where they are used in order to suppress
    # -Werror=date-time:
    find /linuxcan/ -type f -exec sed -i 's/^.*__TIME__.*$//g' {} \; && \
    find /linuxcan/ -type f -exec sed -i 's/^.*__TIMESTAMP__.*$//g' {} \; && \
    find /linuxcan/ -type f -exec sed -i 's/^.*__DATE__.*$//g' {} \; && \
    # Use pragma to suppress -Werror=frame-larger-than= (this could also be
    # used for the timestamps):
    sed -i '1i#pragma GCC diagnostic push' /linuxcan/common/util.c && \
    sed -i '1i#pragma GCC diagnostic ignored "-Wframe-larger-than="' /linuxcan/common/util.c && \
    echo '#pragma GCC diagnostic pop' >> /linuxcan/common/util.c && \
    cd linuxcan && \
    make && \
    make install && \
    rm /linuxcan.tar.gz

# Install additional prerequisites for getting and testing canStream:
RUN apt-get update && apt-get install -y \
    vim \
    alsa-utils \
    unzip \
    --no-install-recommends && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Getting and making canStream:
RUN wget --no-check-certificate https://github.com/skymandr/canStream/archive/master.zip && \
    unzip master.zip && \
    mv canStream-master canStream && \
    cd canStream && \
    make
