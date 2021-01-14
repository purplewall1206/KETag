```
static inline pgd_t *pgd_offset_pgd(pgd_t *pgd, unsigned long address)
{
	return (pgd + pgd_index(address));
};

/*
 * a shortcut to get a pgd_t in a given mm
 */
#ifndef pgd_offset
#define pgd_offset(mm, address)		pgd_offset_pgd((mm)->pgd, (address))
#endif
```

[  681.314918] pgd : ffff88816c6beff8  260f067, index: 511
[  681.314918] p4d : ffff88816c6beff8  260f067, index: 0
[  681.314918] pud : ffff88800260fff0  2610063, index: 510
[  681.314919] pmd: ffff888002610040, 10000e1

[ 3565.996698] pgd : ffff88816c774ff8  260f067, index: 511
[ 3565.996699] p4d : ffff88816c774ff8  260f067, index: 0
[ 3565.996699] pud : ffff88800260fff0  2610063, index: 510
[ 3565.996699] pmd: ffff888002610040, 10000e1

[66142.314600] pgd : ffff88816dba2ff8  260f067, index: 511
[66142.314601] p4d : ffff88816dba2ff8  260f067, index: 0
[66142.314601] pud : ffff88800260fff0  2610063, index: 510
[66142.314602] pmd: ffff888002610040, 10000e1

[66174.946284] pgd : ffff8881488deff8  260f067, index: 511
[66174.946285] p4d : ffff8881488deff8  260f067, index: 0
[66174.946285] pud : ffff88800260fff0  2610063, index: 510
[66174.946285] pmd: ffff888002610040, 10000e1
[66174.955330] hello exit