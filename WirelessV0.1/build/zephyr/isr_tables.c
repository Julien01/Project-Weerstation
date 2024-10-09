
/* AUTO-GENERATED by gen_isr_tables.py, do not edit! */

#include <zephyr/toolchain.h>
#include <zephyr/linker/sections.h>
#include <zephyr/sw_isr_table.h>
#include <zephyr/arch/cpu.h>

typedef void (* ISR)(const void *);
uintptr_t __irq_vector_table _irq_vector_table[31] = {
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
	((uintptr_t)&_isr_wrapper),
};
struct _isr_table_entry __sw_isr_table _sw_isr_table[31] = {
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 0 */
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 1 */
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 2 */
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 3 */
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 4 */
	{(const void *)0x800c450, (ISR)0x8005161}, /* 5 */
	{(const void *)0x800c44e, (ISR)0x8005161}, /* 6 */
	{(const void *)0x800c44c, (ISR)0x8005161}, /* 7 */
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 8 */
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 9 */
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 10 */
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 11 */
	{(const void *)0x0, (ISR)0x80056fd}, /* 12 */
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 13 */
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 14 */
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 15 */
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 16 */
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 17 */
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 18 */
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 19 */
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 20 */
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 21 */
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 22 */
	{(const void *)0x800b97c, (ISR)0x8005d55}, /* 23 */
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 24 */
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 25 */
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 26 */
	{(const void *)0x800b954, (ISR)0x800b10d}, /* 27 */
	{(const void *)0x800b940, (ISR)0x800b10d}, /* 28 */
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 29 */
	{(const void *)0x0, (ISR)z_irq_spurious}, /* 30 */
};