# $FreeBSD: src/share/mk/bsd.port.pre.mk,v 1.4.36.1.6.1 2010/12/21 17:09:25 kensmith Exp $

BEFOREPORTMK=	yes

.include <bsd.port.mk>

.undef BEFOREPORTMK
