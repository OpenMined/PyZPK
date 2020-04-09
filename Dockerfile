FROM ubuntu:19.04

# Set environment variables.
ENV HOME /root
ENV PATH "/root/bin:${PATH}"

# Define working directory.
WORKDIR /root

RUN apt update
RUN apt install -y python3.7 python3-pip git cmake pkg-config
RUN apt install -y build-essential cmake git libgmp3-dev libprocps-dev python-markdown libboost-all-dev libssl-dev

WORKDIR /root/PyZPK
COPY . /root/PyZPK

RUN \
    bash build.sh && \
    pip3 install -r requirements_dev.txt && \
    pip3 install -r requirements.txt

# Define default command.
CMD ["bash"]