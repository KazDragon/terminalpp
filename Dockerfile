FROM ubuntu:24.04

RUN apt-get update && DEBIAN_FRONTEND=noninteractive
RUN apt-get install -y g++ vim cmake git gdb wget libboost1.83-all-dev

ARG PROJECT=terminalpp
ARG USERNAME=ubuntu

# Create the user
RUN apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

USER $USERNAME

WORKDIR /workspaces/$PROJECT