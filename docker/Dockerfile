#
# Simple docker image which can be used as the ebplane dev environment
#
# Build the disk:
#   $ docker build -t "ebplane_volume" .
#
#
# Run the docker container and leave it running in the background (also map a
# local folder in /scrah):
#   $ docker run -P -h ebplane --name ebplane -d -v ~/Documents/Scratch:/scratch ebplane_volume
#
# Now you can access the running container either directly trough docker:
#   $ docker exec -it ebplane bash
#
# Or via SSH, but you first need to get the local ssh port (password: ebplane):
#   $ docker port ebplane 22
#   0.0.0.0:32769
#   $ ssh root@localhost -p 32768
#
#
# Start the container as a one off to build and once done you exit:
#   $ docker run -h ebplane -itv ~/Documents/Scratch:/scratch ebplane_volume bash
#
#
#
# NOTE: if enabled selinux might block access to your scratch directory:
#         $ chcon -Rt svirt_sandbox_file_t ~/Documents/Scratch
#

#
# Use latest Fedora distribution as base image
#
FROM fedora:latest


#
# Update existing packages, and install some additional ones
#
RUN dnf -y update && \
    dnf -y install \ 
	autoconf \
	automake \
	clang \
	emacs-nox \
	findutils \
	gcc \
	gcc-c++ \
	gdb \
	git \
	glibc-devel.i686 \
	make \
	openssh-server \
	unzip \
	wget \
	which \
	zip \
	zlib-devel


#
# Install Bazel v0.29.1 (any newer will currently not build ebPlane)
#
RUN wget https://github.com/bazelbuild/bazel/releases/download/0.29.1/bazel-0.29.1-installer-linux-x86_64.sh
RUN chmod +x bazel-0.29.1-installer-linux-x86_64.sh
RUN ./bazel-0.29.1-installer-linux-x86_64.sh


#
# Make sure you can access it trough SSH and end up in /scratch
#
RUN mkdir /var/run/sshd
RUN echo 'root:ebplane' | chpasswd
RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config
RUN /usr/bin/ssh-keygen -A


#
# Expose ssh port 22 and start the ssh daemon
#
EXPOSE 22
CMD ["/usr/sbin/sshd", "-D"]


#
# Auto move to the /scratch directory
#
VOLUME /scratch
RUN echo "cd /scratch" >> /root/.bashrc
