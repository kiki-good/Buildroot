/* Generated by ./xlat/gen.sh from ./xlat/sigemt_codes.in; do not edit. */
#if !(defined(EMT_TAGOVF) || (defined(HAVE_DECL_EMT_TAGOVF) && HAVE_DECL_EMT_TAGOVF))
# define EMT_TAGOVF 1
#endif

#ifdef IN_MPERS

extern const struct xlat sigemt_codes[];

#else

# if !(defined HAVE_M32_MPERS || defined HAVE_MX32_MPERS)
static
# endif
const struct xlat sigemt_codes[] = {
 XLAT(EMT_TAGOVF),
 XLAT_END
};

#endif /* !IN_MPERS */