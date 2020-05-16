#include <stdio.h>

#define NNG_STATIC_LIB
#include <nng/nng.h>
#include <nng/protocol/pubsub0/pub.h>
#include <nng/protocol/pubsub0/sub.h>
#include <nng/protocol/reqrep0/rep.h>
#include <nng/protocol/reqrep0/req.h>
#include <nng/supplemental/util/platform.h>

#include "csc/csc_debug_nng.h"

#define ADDRESS_SUB "ipc:///glshape_sub"
#define ADDRESS_PUB "ipc:///glshape_pub"




int main(int argc, char **argv)
{
	nng_socket sub;
	nng_socket pub;
	{
		int r;
		r = nng_sub0_open (&sub);
		NNG_EXIT_ON_ERROR (r);
		r = nng_listen (sub, ADDRESS_PUB, NULL, 0);
		NNG_EXIT_ON_ERROR (r);
		r = nng_setopt (sub, NNG_OPT_SUB_SUBSCRIBE, "", 0);
		NNG_EXIT_ON_ERROR (r);
	}
	{
		int r;
		r = nng_pub0_open (&pub);
		NNG_EXIT_ON_ERROR (r);
		r = nng_listen (pub, ADDRESS_SUB, NULL, 0);
		NNG_EXIT_ON_ERROR (r);
	}

	while (1)
	{
		int rv;
		size_t   sz;
		float * val = NULL;
		rv = nng_recv (sub, &val, &sz, NNG_FLAG_ALLOC);
		if (rv == 0)
		{
			rv = nng_send (pub, val, sz, 0);
		}
		nng_free (val, sz);
		printf ("New message %i\n", sz);
	}
}


