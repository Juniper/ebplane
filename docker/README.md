# Docker build container

This directory contains a Docker definition file that can be used to get a 
simple build environment setup. See the header in the [Dockerfile](Dockerfile)
itself on various ways you could start and connect to the container.

Below we will go through the basic steps on how to build the Docker volume, and
container and successfully build and test the ebplane project.


## Prerecuitistes on your host machine

* First make sure Docker has been installed successfully
* Secondly create the ~/Documents/Scratch directory and clone the ebplane project:

```
[host:~]$ mkdir ~/Documents/Scratch/
[host:~]$ cd ~/Documents/Scratch/
[host:~/Documents/Scratch]$ git clone https://github.com/Juniper/ebplane.git
Cloning into 'ebplane'...
remote: Enumerating objects: 14, done.
remote: Counting objects: 100% (14/14), done.
remote: Compressing objects: 100% (14/14), done.
remote: Total 391 (delta 2), reused 6 (delta 0), pack-reused 377
Receiving objects: 100% (391/391), 92.07 KiB | 736.00 KiB/s, done.
Resolving deltas: 100% (190/190), done
```


## Build the Docker volume
The below command creates the _ebplane\_volume_ which can be used later by the 
Docker container.

```
[host:~]$ cd ~/Documents/Scratch/ebplane/docker
[host:~/...ratch/ebplane/docker]$ docker build -t "ebplane_volume" .
Sending build context to Docker daemon  5.632kB
Step 1/13 : FROM fedora:latest
 ---> c582c1438f27
...
...
Step 13/13 : RUN echo "cd /scratch" >> /root/.bashrc
 ---> Running in 327a5e0e968d
Removing intermediate container 327a5e0e968d
 ---> 5befe28e30eb
Successfully built 5befe28e30eb
Successfully tagged ebplane_volume:latest
```

## Start the Docker container

We can start the container in the background and connect to it whenever needed,
or start an instance and use it for the time being. See the header in the
[Dockerfile](Dockerfile) for some examples. Here we will start a container and
use it interactively.

```
[host:~/...ratch/ebplane/docker]$ docker run -h ebplane -itv ~/Documents/Scratch:/scratch ebplane_volume bash
[root@ebplane scratch]# 
```

## Now build and run the unit tests

Now that we are attached to the Docker container we can build all the binaries:

```
[root@ebplane scratch]# cd ebplane
[root@ebplane ebplane]# bazel build ...:all
Extracting Bazel installation...
Starting local Bazel server and connecting to it...
INFO: Analyzed 31 targets (37 packages loaded, 67557 targets configured).
INFO: Found 31 targets...
INFO: From CcGnumakeMakeRule external/linuxsrc/installhdr/include:

INFO: From CcConfigureMakeRule external/elfutils/libelf/include:

INFO: From CcGnumakeMakeRule external/libbpf/libbpf/include:

INFO: Elapsed time: 246.150s, Critical Path: 83.71s
INFO: 74 processes: 74 processwrapper-sandbox.
INFO: Build completed successfully, 146 total actions
```

And finish it off with running the unit tests:

```
[root@ebplane ebplane]# bazel test ...:all
INFO: Analyzed 31 targets (0 packages loaded, 0 targets configured).
INFO: Found 15 targets and 16 test targets...
INFO: Elapsed time: 2.438s, Critical Path: 0.18s
INFO: 16 processes: 16 processwrapper-sandbox.
INFO: Build completed successfully, 17 total actions
//build/tests:ebpf_test                                                  PASSED in 0.0s
//build/tests:embed_test_dependency                                      PASSED in 0.1s
//build/tests:embed_test_library                                         PASSED in 0.0s
//build/tests:embed_test_multiple                                        PASSED in 0.0s
//build/tests:embed_test_simple                                          PASSED in 0.1s
//daemon:main_test                                                       PASSED in 0.1s
//lib/base:opaque_value_test                                             PASSED in 0.0s
//lib/base:unique_value_test                                             PASSED in 0.0s
//lib/error:assign_or_return_test                                        PASSED in 0.1s
//lib/error:code_test                                                    PASSED in 0.0s
//lib/error:return_if_error_test                                         PASSED in 0.0s
//lib/error:status_or_test                                               PASSED in 0.0s
//lib/error:status_test                                                  PASSED in 0.0s
//lib/posix:errno_test                                                   PASSED in 0.0s
//lib/posix:unique_file_descriptor_test                                  PASSED in 0.0s
//lib/tests:xdp_loader_test                                              PASSED in 0.0s

Executed 16 out of 16 tests: 16 tests pass.
INFO: Build completed successfully, 17 total actions
```


