# $FreeBSD: src/share/mk/bsd.port.mk,v 1.309.10.1.6.1 2010/12/21 17:09:25 kensmith Exp $

PORTSDIR?=	/usr/ports
BSDPORTMK?=	${PORTSDIR}/Mk/bsd.port.mk

# Needed to keep bsd.own.mk from reading in /etc/src.conf
# and setting MK_* variables when building ports.
_WITHOUT_SRCCONF=

.include <bsd.own.mk>
.include "${BSDPORTMK}"
