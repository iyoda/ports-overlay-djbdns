PORTNAME=	djbdns
PORTVERSION=	1.05
CATEGORIES=	dns
MASTER_SITES=	http://cr.yp.to/djbdns/:main \
		http://smarden.org/pape/djb/manpages/:man \
		http://www.fefe.de/dns/:ipv6
DISTFILES=	${DISTNAME}${EXTRACT_SUFX}:main \
		${DISTNAME}-man-${MANDATE}.tar.gz:man
DIST_SUBDIR=	${PORTNAME}

PATCH_SITES=	http://www.fefe.de/dns/:ipv6
PATCHFILES=	${DISTNAME}-test32.diff.xz:ipv6
PATCH_DIST_STRIP=	-p1

MAINTAINER=	iyoda@atikoro.net
COMMENT=	Collection of authoritative DNS tools by Daniel J. Bernstein
WWW=		https://cr.yp.to/djbdns.html

LICENSE=	PD

RUN_DEPENDS=	svscan:sysutils/daemontools

USES=		cpe
CPE_VENDOR=	djbdns_project

OPTIONS_DEFINE=		AXFRDNS DNSCACHE MAN
OPTIONS_DEFAULT=	AXFRDNS MAN
OPTIONS_SUB=		yes

AXFRDNS_DESC=		Include axfrdns zone transfer daemon
AXFRDNS_RUN_DEPENDS=	tcpserver:sysutils/ucspi-tcp
DNSCACHE_DESC=		Include dnscache recursive resolver (not recommended for new deployments)
MAN_DESC=		Install manual pages

MANDATE=	20031023

USERS=		dnscache tinydns dnslog
GROUPS=		dnscache tinydns dnslog

ALL_TARGET=	prog
INSTALL_TARGET=	setup check

CONFLICTS_INSTALL=	djbdnscurve6

post-extract:
	@${MV} ${WRKDIR}/${PORTNAME}-man ${WRKSRC}/man
	@${CP} ${FILESDIR}/qmerge.c ${WRKSRC}/qmerge.c
	@${CP} ${FILESDIR}/qmerge.h ${WRKSRC}/qmerge.h
	@${CP} ${FILESDIR}/maxclient.h ${WRKSRC}/maxclient.h

post-patch:
	@${ECHO_CMD} "${CC} ${CFLAGS} -O2 -fno-strict-aliasing -include errno.h" > ${WRKSRC}/conf-cc
	@${ECHO_CMD} "${CC} ${STRIP} ${LDFLAGS}" > ${WRKSRC}/conf-ld
	@${ECHO_CMD} "${STAGEDIR}${PREFIX}" > ${WRKSRC}/conf-home.stage
	@${ECHO_CMD} "${PREFIX}" > ${WRKSRC}/conf-home

post-build:
	@${ECHO_MSG} "===> Rebuilding installer for STAGEDIR"
	@${MV} -f ${WRKSRC}/conf-home ${WRKSRC}/conf-home.sav
	@${MV} -f ${WRKSRC}/conf-home.stage ${WRKSRC}/conf-home
	@cd ${WRKSRC} && ${RM} install instcheck install.o instcheck.o hier.o auto_home.o auto_home.c
	@cd ${WRKSRC} && ${DO_MAKE_BUILD} install instcheck
	@${TOUCH} ${WRKSRC}/*-conf
	@${MV} -f ${WRKSRC}/conf-home.sav ${WRKSRC}/conf-home

post-install-MAN-on:
	@${MKDIR} ${STAGEDIR}${PREFIX}/share/man/man1
	@${MKDIR} ${STAGEDIR}${PREFIX}/share/man/man5
	@${MKDIR} ${STAGEDIR}${PREFIX}/share/man/man8
	${INSTALL_MAN} ${WRKSRC}/man/*.1 ${STAGEDIR}${PREFIX}/share/man/man1/
	${INSTALL_MAN} ${WRKSRC}/man/*.5 ${STAGEDIR}${PREFIX}/share/man/man5/
	${INSTALL_MAN} ${WRKSRC}/man/*.8 ${STAGEDIR}${PREFIX}/share/man/man8/

.include <bsd.port.mk>
