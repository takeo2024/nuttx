/****************************************************************************
 * arch/z80/include/z80/irq.h
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/* This file should never be included directly but, rather,
 * only indirectly through nuttx/irq.h (via arch/irq.h)
 */

#ifndef __ARCH_Z80_INCLUDE_Z80_IRQ_H
#define __ARCH_Z80_INCLUDE_Z80_IRQ_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#ifndef __ASSEMBLY__
#  include <stdint.h>
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Z80 Interrupts */

#define Z80_RST0         (0)
#define Z80_RST1         (1)
#define Z80_RST2         (2)
#define Z80_RST3         (3)
#define Z80_RST4         (4)
#define Z80_RST5         (5)
#define Z80_RST6         (6)
#define Z80_RST7         (7)

#define Z80_IRQ_SYSTIMER Z80_RST7
#define NR_IRQS          (8)

/* IRQ Stack Frame Format
 *
 * This stack frame is created on each interrupt.  These registers are stored
 * in the TCB to many context switches.
 */

#define XCPT_I               (0) /* Offset 0: Saved I w/interrupt state in carry */
#define XCPT_BC              (1) /* Offset 1: Saved BC register */
#define XCPT_DE              (2) /* Offset 2: Saved DE register */
#define XCPT_IX              (3) /* Offset 3: Saved IX register */
#define XCPT_IY              (4) /* Offset 4: Saved IY register */
#define XCPT_SP              (5) /* Offset 5: Offset to SP at time of interrupt */
#define XCPT_HL              (6) /* Offset 6: Saved HL register */
#define XCPT_AF              (7) /* Offset 7: Saved AF register */
#define XCPT_PC              (8) /* Offset 8: Offset to PC at time of interrupt */

#define XCPTCONTEXT_REGS     (9)
#define XCPTCONTEXT_SIZE     (2 * XCPTCONTEXT_REGS)

/****************************************************************************
 * Public Types
 ****************************************************************************/

#ifndef __ASSEMBLY__

/* This is the type of the register save array */

typedef uint16_t chipreg_t;

/* This struct defines the way the registers are stored. */

struct xcptcontext
{
  /* Register save area */

  chipreg_t regs[XCPTCONTEXT_REGS];

  /* The following retains that state during signal execution.
   *
   * REVISIT:  Because there is only one copy of these save areas,
   * only a single signal handler can be active.  This precludes
   * queuing of signal actions.  As a result, signals received while
   * another signal handler is executing will be ignored!
   */

  uint16_t saved_pc;    /* Saved return address */
  uint16_t saved_i;     /* Saved interrupt state */
};
#endif

/****************************************************************************
 * Inline functions
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifndef __ASSEMBLY__
#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/* Name: up_irq_save, up_irq_restore, and friends.
 *
 * NOTE: This function should never be called from application code and,
 * as a general rule unless you really know what you are doing, this
 * function should not be called directly from operation system code either:
 * Typically, the wrapper functions, enter_critical_section() and
 * leave_critical section(), are probably what you really want.
 */

irqstate_t up_irq_save(void) __naked;
void       up_irq_restore(irqstate_t flags) __naked;
irqstate_t up_irq_enable(void);

#undef EXTERN
#ifdef __cplusplus
}
#endif
#endif

#endif /* __ARCH_Z80_INCLUDE_Z80_IRQ_H */
