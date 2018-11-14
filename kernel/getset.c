#include "kernel/calls.h"

dword_t sys_getpid() {
    STRACE("getpid()");
    return current->tgid;
}
dword_t sys_gettid() {
    STRACE("gettid()");
    return current->pid;
}
dword_t sys_getppid() {
    STRACE("getppid()");
    pid_t_ ppid;
    lock(&pids_lock);
    if (current->parent != NULL)
        ppid = current->parent->pid;
    else
        ppid = 0;
    unlock(&pids_lock);
    return ppid;
}
dword_t sys_getpgid(dword_t pid) {
    STRACE("getpgid(%d)", pid);
    if (pid != 0)
        return _EPERM;
    return current->pgid;
}
dword_t sys_getpgrp() {
    STRACE("getpgrp()");
    return current->pgid;
}

dword_t sys_getuid32() {
    STRACE("getuid32()");
    return current->uid;
}
dword_t sys_getuid() {
    STRACE("getuid()");
    return current->uid & 0xffff;
}

dword_t sys_setuid32(uid_t_ uid) {
    STRACE("setuid32(%d)", uid);
    if (current->uid > 0 && current->euid > 0)
        return _EPERM;
    current->uid = uid;
    current->euid = uid;
    current->suid = uid;
    return 0;
}
dword_t sys_setuid(uid_t_ uid) {
    STRACE("setuid(%d)", uid);
    if (current->uid > 0 && current->euid > 0)
        return _EPERM;
    current->uid = uid;
    current->euid = uid;
    current->suid = uid;
    return 0;
}

dword_t sys_setreuid32(uid_t_ uid, uid_t_ euid) {
    STRACE("setuid32(%d, %d)", uid, euid);
    if (current->uid > 0 && current->euid > 0 && uid != -1 && euid != current->uid && euid != current->suid)
        return _EPERM;
    if (uid != -1)
        current->uid = uid;
    if (euid != -1)
        current->euid = uid;
    return 0;
}
dword_t sys_setreuid(uid_t_ uid, uid_t_ euid) {
    STRACE("setreuid(%d, %d)", uid, euid);
    if (current->uid > 0 && current->euid > 0 && uid != -1 && euid != current->uid && euid != current->suid)
        return _EPERM;
    if (uid != -1)
        current->uid = uid;
    if (euid != -1)
        current->euid = uid;
    return 0;
}

dword_t sys_geteuid32() {
    STRACE("geteuid32()");
    return current->euid;
}
dword_t sys_geteuid() {
    STRACE("geteuid()");
    return current->euid & 0xffff;
}

dword_t sys_setresuid(uid_t_ ruid, uid_t_ euid, uid_t_ suid) {
    STRACE("setresuid(%d, %d, %d)", ruid, euid, suid);
    if (euid != current->uid && euid != current->suid && current->uid > 0 && current->euid > 0 && ruid != -1 && suid != -1)
        return _EPERM;
    if (ruid != -1)
        current->uid = ruid;
    if (euid != -1)
        current->euid = euid;
    if (suid != -1)
        current->suid = suid;
    return 0;
}

dword_t sys_getgid32() {
    STRACE("getgid32()");
    return current->gid;
}
dword_t sys_getgid() {
    STRACE("getgid()");
    return current->gid & 0xffff;
}

dword_t sys_getegid32() {
    STRACE("getegid32()");
    return current->egid;
}
dword_t sys_getegid() {
    STRACE("getegid()");
    return current->egid & 0xffff;
}

dword_t sys_setresgid(uid_t_ rgid, uid_t_ egid, uid_t_ sgid) {
    STRACE("setresgid(%d, %d, %d)", rgid, egid, sgid);
    if (current->uid > 0 || current->euid > 0)
        return _EPERM;
    if (rgid != -1)
        current->gid = rgid;
    if (egid != -1)
        current->egid = egid;
    if (sgid != -1)
        current->sgid = sgid;
    return 0;
}

