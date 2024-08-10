FROM ubuntu:22.04

RUN apt-get update && DEBIAN_FRONTEND=noninteractive

ARG USERNAME=terminalpp
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Create the user
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME --shell /bin/bash \
    #
    # [Optional] Add sudo support. Omit if you don't need to install software after connecting.
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

USER $USERNAME

WORKDIR /workspace/$USERNAME

RUN apt-get install -y g++ vim cmake git gdb wget libboost1.74-all-dev
RUN apt-get install -y libfmt-dev

RUN mkdir /workspace/$USERNAME/ext \
    && EXTERNAL_ROOT=/workspace/$USERNAME/ext /workspace/$USERNAME/.ci/fetch_system_dependencies.sh