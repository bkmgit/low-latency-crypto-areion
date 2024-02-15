/* Copyright (c) 2023 GMO Cybersecurity by Ierae, Inc. All rights reserved. */
/* Modification based on https://xyxj1024.github.io/blog/arm-pmu */
/* by Xingjian Xuanyuan */

#define _GNU_SOURCE
#include <linux/perf_event.h>    /* Definition of PERF_* constants */
#include <linux/hw_breakpoint.h> /* Definition of HW_* constants */
#include <sys/syscall.h>         /* Definition of SYS_* constants */
#include <sys/ioctl.h>
#include <assert.h>
#include <unistd.h>
#include <asm/unistd.h>

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "areion.h"
#include "cycle.h"

#define NUMBER_OF_LOOPS 12500000

static long
perf_event_open(struct perf_event_attr *hw_event, pid_t pid,
                int cpu, int group_fd, unsigned long flags)
{
    int ret;
    ret = syscall(__NR_perf_event_open, hw_event, pid, cpu, group_fd, flags);
    return ret;
}

static void fill(uint8_t *dst, size_t len)
{
    for (size_t i = 0; i < len; i++) {
        dst[i] = i;
    }
}

static void benchmark_primitives()
{
    {
        struct perf_event_attr pe;
        int ccnt_fd, rc;
        unsigned long long c1, c2;
        uint8_t in[32];
        uint8_t out[32];
        fill(in, sizeof in);

        memset(&pe, 0, sizeof(struct perf_event_attr));
        pe.disabled = 0;                            // start disabled
        pe.type = PERF_TYPE_HARDWARE;               // "generalized" hardware events
        pe.exclude_hv = 1;                          // exclude hypervisor
        pe.size = sizeof(struct perf_event_attr);   // allow the kernel to see the struct size at the time of compilation
        pe.enable_on_exec = 1;                      // auto enable on exec
        pe.inherit = 1;                             // count children
        pe.exclude_kernel = 1;                      // excludes events that happen in kernel space
        pe.config = PERF_COUNT_HW_CPU_CYCLES;       // total cycles

        ccnt_fd = perf_event_open(&pe, getpid(), -1, -1, 0);
        if (ccnt_fd < 0) {
            perror("perf_event_open for CPU cycles failed");
            exit(EXIT_FAILURE);
        }
        rc = read(ccnt_fd, &c1, sizeof(c1)); assert(rc);
        for (int i = 0; i < NUMBER_OF_LOOPS; i++) {
            permute_areion_256u8(out, in);
        }
        rc = read(ccnt_fd, &c2, sizeof(c2)); assert(rc);
        double total_cycle = c2 - c1;;
        total_cycle /= NUMBER_OF_LOOPS;
        total_cycle /= 32;
        printf("permute_areion_256u8: %g\n", total_cycle);
    }
    {
        struct perf_event_attr pe;
        int ccnt_fd, rc;
        unsigned long long c1, c2;
        uint8_t in[32];
        uint8_t out[32];
        fill(in, sizeof in);
        memset(&pe, 0, sizeof(struct perf_event_attr));
        pe.disabled = 0;                            // start disabled
        pe.type = PERF_TYPE_HARDWARE;               // "generalized" hardware events
        pe.exclude_hv = 1;                          // exclude hypervisor
        pe.size = sizeof(struct perf_event_attr);   // allow the kernel to see the struct size at the time of compilation
        pe.enable_on_exec = 1;                      // auto enable on exec
        pe.inherit = 1;                             // count children
        pe.exclude_kernel = 1;                      // excludes events that happen in kernel space
        pe.config = PERF_COUNT_HW_CPU_CYCLES;       // total cycles

        ccnt_fd = perf_event_open(&pe, getpid(), -1, -1, 0);
        if (ccnt_fd < 0) {
            perror("perf_event_open for CPU cycles failed");
            exit(EXIT_FAILURE);
        }
        rc = read(ccnt_fd, &c1, sizeof(c1)); assert(rc);

        for (int i = 0; i < NUMBER_OF_LOOPS; i++) {
            inverse_areion_256u8(out, in);
        }
        rc = read(ccnt_fd, &c2, sizeof(c2)); assert(rc);
        double total_cycle = c2 - c1;
        total_cycle /= NUMBER_OF_LOOPS;
        total_cycle /= 32;
        printf("inverse_areion_256u8: %g\n", total_cycle);
    }
    {
        struct perf_event_attr pe;
        int ccnt_fd, rc;
        unsigned long long c1, c2;
        uint8_t in[64];
        uint8_t out[64];
        fill(in, sizeof in);
        memset(&pe, 0, sizeof(struct perf_event_attr));
        pe.disabled = 0;                            // start disabled
        pe.type = PERF_TYPE_HARDWARE;               // "generalized" hardware events
        pe.exclude_hv = 1;                          // exclude hypervisor
        pe.size = sizeof(struct perf_event_attr);   // allow the kernel to see the struct size at the time of compilation
        pe.enable_on_exec = 1;                      // auto enable on exec
        pe.inherit = 1;                             // count children
        pe.exclude_kernel = 1;                      // excludes events that happen in kernel space
        pe.config = PERF_COUNT_HW_CPU_CYCLES;       // total cycles

        ccnt_fd = perf_event_open(&pe, getpid(), -1, -1, 0);
        if (ccnt_fd < 0) {
            perror("perf_event_open for CPU cycles failed");
            exit(EXIT_FAILURE);
        }
        rc = read(ccnt_fd, &c1, sizeof(c1)); assert(rc);

        for (int i = 0; i < NUMBER_OF_LOOPS; i++) {
            permute_areion_512u8(out, in);
        }
        rc = read(ccnt_fd, &c2, sizeof(c2)); assert(rc);
        double total_cycle = c2 - c1;
        total_cycle /= NUMBER_OF_LOOPS;
        total_cycle /= 32;
        printf("permute_areion_512u8: %g\n", total_cycle);
    }
    {
        struct perf_event_attr pe;
        int ccnt_fd, rc;
        unsigned long long c1, c2;
        uint8_t in[64];
        uint8_t out[64];
        fill(in, sizeof in);
        memset(&pe, 0, sizeof(struct perf_event_attr));
        pe.disabled = 0;                            // start disabled
        pe.type = PERF_TYPE_HARDWARE;               // "generalized" hardware events
        pe.exclude_hv = 1;                          // exclude hypervisor
        pe.size = sizeof(struct perf_event_attr);   // allow the kernel to see the struct size at the time of compilation
        pe.enable_on_exec = 1;                      // auto enable on exec
        pe.inherit = 1;                             // count children
        pe.exclude_kernel = 1;                      // excludes events that happen in kernel space
        pe.config = PERF_COUNT_HW_CPU_CYCLES;       // total cycles

        ccnt_fd = perf_event_open(&pe, getpid(), -1, -1, 0);
        if (ccnt_fd < 0) {
            perror("perf_event_open for CPU cycles failed");
            exit(EXIT_FAILURE);
        }
        rc = read(ccnt_fd, &c1, sizeof(c1)); assert(rc);

        for (int i = 0; i < NUMBER_OF_LOOPS; i++) {
            inverse_areion_512u8(out, in);
        }
        rc = read(ccnt_fd, &c2, sizeof(c2)); assert(rc);
        double total_cycle = c2 - c1; 
        total_cycle /= NUMBER_OF_LOOPS;
        total_cycle /= 32;
        printf("inverse_areion_512u8: %g\n", total_cycle);
    }
}

static void benchmark_aead()
{
    {
        for (int len = 32; len < 4096; len *= 2) {
            struct perf_event_attr pe;
            int ccnt_fd, rc;
            unsigned long long c1, c2;
            uint8_t in[len];
            uint8_t out[len];
            uint8_t tag[16];
            uint8_t h[16];
            uint8_t n[16];
            uint8_t k[16];
            fill(in, sizeof in);
            fill(h, sizeof h);
            fill(n, sizeof n);
            fill(k, sizeof k);
            memset(&pe, 0, sizeof(struct perf_event_attr));
            pe.disabled = 0;                            // start disabled
            pe.type = PERF_TYPE_HARDWARE;               // "generalized" hardware events
            pe.exclude_hv = 1;                          // exclude hypervisor
            pe.size = sizeof(struct perf_event_attr);   // allow the kernel to see the struct size at the time of compilation
            pe.enable_on_exec = 1;                      // auto enable on exec
            pe.inherit = 1;                             // count children
            pe.exclude_kernel = 1;                      // excludes events that happen in kernel space
            pe.config = PERF_COUNT_HW_CPU_CYCLES;       // total cycles

            ccnt_fd = perf_event_open(&pe, getpid(), -1, -1, 0);
            if (ccnt_fd < 0) {
                perror("perf_event_open for CPU cycles failed");
                exit(EXIT_FAILURE);
            }
            rc = read(ccnt_fd, &c1, sizeof(c1)); assert(rc);

            for (int i = 0; i < NUMBER_OF_LOOPS; i++) {
                encrypt_areion_256_opp(out, tag, h, sizeof h, in, sizeof in, n, k);
            }
            rc = read(ccnt_fd, &c2, sizeof(c2)); assert(rc);
            double total_cycle = c2 - c1;
            total_cycle /= NUMBER_OF_LOOPS;
            total_cycle /= len;
            printf("encrypt_areion_256_opp,mlen=%d: %g\n", len,total_cycle);
        };
    }
}

int main(int argc, char **argv)
{
    benchmark_primitives();
    benchmark_aead();

    return 0;
}

