#ifndef _ISOMAC
/* Macros for accessing h_errno from inside libc.  */
# undef  h_errno
# ifdef _LIBC_REENTRANT
#  include <tls.h>
#  ifndef NOT_IN_libc
#   define h_errno __libc_h_errno
#  else
#   define h_errno h_errno	/* For #ifndef h_errno tests.  */
#  endif

/* Description of data base entry for a single network.  NOTE: here a
   poor assumption is made.  The network number is expected to fit
   into an unsigned long int variable.  */
struct netent
{
  char *n_name;			/* Official name of network.  */
  char **n_aliases;		/* Alias list.  */
  int n_addrtype;		/* Net address type.  */
  uint32_t n_net;		/* Network number.  */
}; 

extern __thread int h_errno attribute_tls_model_ie;
# else
extern int h_errno;
# endif	/* _LIBC_REENTRANT */
# define __set_h_errno(x) (h_errno = (x))

#undef DECLARE_NSS_PROTOTYPES
#endif
