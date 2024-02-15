# Low Latency Cryptography Areion
## About

This software provides a reference code of the low-latency cryptographic permutation algorithm Areion and includes applications such as AEAD processing mode OPP. It should be noted that this software is provided as a reference and has not been optimized.

For more information on Areion, visit: https://eprint.iacr.org/2023/794

## Support Architecture
To run this software, the following environmental requirements are necessary.
- SIMD
- Aarch64 architecture (with AES support)

We have confirmed that this software can be built and executed on the following OS.
- Fedora 41

Note. Fedora is a registered trademark of Red Hat Inc. in the United States and other countries.

## How to build

```
$ sudo dnf update
$ sudo dnf -y install make cmake gcc gcc-g++
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=NONE \
  -DCMAKE_CXX_FLAGS=-march=armv8-a+fp+simd+crypto+crc \
  -DCMAKE_C_FLAGS=-march=armv8-a+fp+simd+crypto+crc ..
$ make
```

## How to Test
```
$ ./areion-test
```
## How to Benchmark
The results of benchmark are given in cpb (cycles per byte).
```
$ ./areion-benchmark 
```

# License
The source code is copyright (c) GMO Cybersecurity by Ierae, Inc., and provided under the MIT license.
The full text is included in the file LICENSE.txt.

To use Arm Neon SSE instructions [sse2neon](https://github.com/DLTcollab/sse2neon) is used. This
header only libray is available under the MIT license.

The benchmark timing code is based on the blog post 
[Counting CPU Cyles with ARM PMU](https://xyxj1024.github.io/blog/arm-pmu)
by Xingjian Xuanyuan.

## Reference
The cryptographic algorithms implemented in this software were proposed in the following research paper.

```
@misc{cryptoeprint:2023/794,
      author = {Takanori Isobe and Ryoma Ito and Fukang Liu and Kazuhiko Minematsu and Motoki Nakahashi and Kosei Sakamoto and Rentaro Shiba},
      title = {Areion: Highly-Efficient Permutations and Its Applications (Extended Version)},
      howpublished = {Cryptology ePrint Archive, Paper 2023/794},
      year = {2023},
      doi = {10.46586/tches.v2023.i2.115-154},
      note = {\url{https://eprint.iacr.org/2023/794}},
      url = {https://eprint.iacr.org/2023/794}
}
```
