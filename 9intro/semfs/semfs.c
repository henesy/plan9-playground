#include <u.h>
#include <libc.h>
#include <auth.h>       // required by lib9p
#include <thread.h>
#include <fcall.h>      // required by lib9p
#include <9p.h>         // definitions for lib9p
#include "sem.h"        // our own definitions

static void
fsattach(Req* r)
{
	r->fid->qid = (Qid){0,0,QTDIR};
	r->ofcall.qid = r->fid->qid;
	respond(r, nil);
}

static void
fscreate(Req* r)
{
	Fid*	fid;
	Qid		q;
	Sem*	s;
	
	fid = r->fid;
	q= fid->qid;
	if(!(q.type&QTDIR)){
		respond(r, "not a directory");
		return;
	}
	s = newsem(r->ifcall.name);
	fid->qid = (Qid){s->id, 0, 0};
	fid->aux = s;
	fid->omode = r->ifcall.mode;
	incref(s);
	r->ofcall.qid = fid->qid;
	respond(r, nil);
}

static void
fsread(Req* r)
{
	Fid*	fid;
	Qid		q;
	Sem*	s;
	char	nl[2] = "\n";
	fid = r->fid;
	q = fid->qid;
	if(q.type&QTDIR){
		dirread9p(r, getdirent, nil);
		respond(r, nil);
		return;
	}
	
	s = fid->aux;
	if(s->tickets > 0){
		s->tickets--;
		readstr(r, nl);
		respond(r, nil);
	} else
			queuereq(s, r);
}

static void
fswrite(Req* r)
{
	
}

static char* fswalk1(Fid* fid, char* name, Qid* qid){ ... }

static char*
fsclone(Fid* fid, Fid* newfid)
{
	Sem*	s;
	
	s = fid->aux;
	if(s != nil)
		incref(s);
	newfid->aux = s;
	return nil;
}

static void fsstat(Req* r){ ... }

static void
fsremove(Req* r)
{
	Req*	q;
	Sem*	s;
	
	s = r->fid->aux;
	while(r = dequeuereq(s))
		respond(q, "file has been removed");
	closesem(s);
	r->fid->aux = nil;
	closesem(s);
	respond(r, nil);
}

static void
freefid(Fid* fid)
{
	Sem*	s;
	
	s = fid->aux;
	fid->aux = nil;
	closesem(s);
}


static Srv sfs=
{
	.attach =       fsattach,
	.create =       fscreate,
	.remove =       fsremove,
	.read   =       fsread,
	.write  =       fswrite,
	.walk1  =       fswalk1,
	.clone  =       fsclone,
	.stat   =       fsstat,
	.destroyfid=    freefid,

};

void
usage(void)
{
	fprint(2, "usage: %s [-D] [-s srv] [-m mnt]\n", argv0);
	threadexitsall("usage");
}

void
threadmain(int argc, char **argv)
{
	char*   mnt;
	char*   srv;

	srv = nil;
	mnt = "/mnt/sem";
	ARGBEGIN{
	case 'D':
		chatty9p++;
		break;
	case 's':
		srv = EARGF(usage());
		break;
	case 'm':
		mnt = EARGF(usage());
		break;
	default:
		usage();
	}ARGEND;

	if(argc!= 0)
		usage();
	threadpostmountsrv(&sfs, srv, mnt, MREPL|MCREATE);
	threadexits(nil);
}
