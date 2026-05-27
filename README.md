# FreeBSD Ports Overlay: dns/djbdns

FreeBSD port for [djbdns](https://cr.yp.to/djbdns.html) 1.05, distributed as a ports overlay.

djbdns was removed from the FreeBSD ports tree on 2023-06-30
([commit 40a6461c](https://cgit.freebsd.org/ports/commit/?id=40a6461c672d727c62129aded50173fc777f3ab0)).
This overlay restores it with security fixes, IPv6 support, and 64-bit portability fixes.

Restoration is being tracked at [FreeBSD Bug #275803](https://bugs.freebsd.org/bugzilla/show_bug.cgi?id=275803).

## Quick Start

```sh
git clone https://github.com/iyoda/ports-overlay-djbdns /usr/local/overlays/djbdns
echo 'OVERLAYS=/usr/local/overlays/djbdns' >> /etc/make.conf
cd /usr/local/overlays/djbdns/dns/djbdns
make install clean
```

With poudriere:

```sh
poudriere bulk -j jail -p default -O /usr/local/overlays/djbdns dns/djbdns
```

## What's Included

### Security Fixes

- **CVE-2008-4392**: Merge similar outgoing queries + SOA record caching (anti-poisoning)
- **CVE-2009-0858**: Response domain name length check (Dempsky fix)
- **CVE-2012-1191**: Ghost domain attack fix

### Patches

- **IPv6**: Felix von Leitner's test32 patch (applied via PATCHFILES)
- **tinydns64**: LP64 uint32 portability fix for 64-bit systems (from pkgsrc)
- **Root hints**: Updated to current IANA root servers (2026-05-21)
- **hier.c**: Install paths relative to PREFIX, fix directory permissions
- **dnscache-conf.c**: Look for dnsroots relative to PREFIX

### Patch Sources

Patches are drawn from established, actively maintained cross-distro sources:

| Source | Version | Maintainer |
|--------|---------|------------|
| Gentoo | 1.05-r42 | Jaco Kroon |
| Debian | 1:1.05-22.1 | Peter Pentchev |
| Alpine Linux | 1.05-r55 | Natanael Copa |
| pkgsrc | 1.05nb16 | schmonz@NetBSD.org |

## Port Details

| Field | Value |
|-------|-------|
| PORTNAME | djbdns |
| PORTVERSION | 1.05 |
| LICENSE | PD (Public Domain, released 2007-12-28) |
| MAINTAINER | (see Makefile) |

### Build Options

| Option | Default | Description |
|--------|---------|-------------|
| AXFRDNS | ON | Include axfrdns zone transfer daemon |
| DNSCACHE | OFF | Include dnscache recursive resolver |
| MAN | ON | Install manual pages |

### Installed Tools

- **tinydns** / **tinydns-conf** / **tinydns-data** / **tinydns-get** / **tinydns-edit** — Authoritative DNS server
- **axfrdns** / **axfrdns-conf** — Zone transfer daemon (AXFRDNS option)
- **dnscache** / **dnscache-conf** — Caching recursive resolver (DNSCACHE option, not recommended for new deployments)
- **rbldns** / **walldns** / **pickdns** — Specialized DNS servers
- **dnsip** / **dnsip6** / **dnsname** / **dnsmx** / **dnstxt** / **dnsq** / **dnsqr** / **dnstrace** — DNS client utilities

### Runtime Dependencies

- [sysutils/daemontools](https://www.freshports.org/sysutils/daemontools/) (service supervision)
- [sysutils/ucspi-tcp](https://www.freshports.org/sysutils/ucspi-tcp/) (when AXFRDNS is enabled)

## Tested On

- FreeBSD 14.4-RELEASE aarch64
- poudriere bulk build: success
- Full cycle: fetch, extract, patch, build, stage, stage-qa, package, install, test, deinstall

## Background

djbdns was created by Daniel J. Bernstein and released in 2001.
The source was placed into the public domain in 2007.

The FreeBSD port was removed with the reason:
"No longer compliant with current DNS standards and source code hasn't been centrally managed for over 20 years."

However, djbdns remains actively maintained across multiple major distributions
(Debian, Gentoo, Alpine Linux, pkgsrc). The primary use case — authoritative DNS
serving with tinydns — continues to work correctly and securely. tinydns is a
minimal, auditable, zero-configuration-file authoritative DNS server that has had
no security vulnerabilities in its core design for over two decades.

## Contributing

Bug reports and patches welcome via GitHub issues.

For the upstream FreeBSD ports restoration effort, see
[Bug #275803](https://bugs.freebsd.org/bugzilla/show_bug.cgi?id=275803).
