/*
 * Copyright (c) 2000-2019 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
 
/*
 */
 
/*
 * basic mach types.
 */
typedef struct task                     *task_t, *task_name_t, *task_inspect_t, *task_read_t, *task_suspension_token_t, *task_policy_set_t, *task_policy_get_t;
typedef struct thread                   *thread_t, *thread_act_t, *thread_inspect_t, *thread_read_t;
typedef struct ipc_space                *ipc_space_t, *ipc_space_read_t, *ipc_space_inspect_t;
typedef struct coalition                *coalition_t;
typedef struct host                     *host_t;
typedef struct host                     *host_priv_t;
typedef struct host                     *host_security_t;
typedef struct processor                *processor_t;
typedef struct processor_set            *processor_set_t;
typedef struct processor_set            *processor_set_control_t;
typedef struct semaphore                *semaphore_t;
typedef struct ledger                   *ledger_t;
typedef struct alarm                    *alarm_t;
typedef struct clock                    *clock_serv_t;
typedef struct clock                    *clock_ctrl_t;
typedef struct arcade_register          *arcade_register_t;
typedef struct ipc_eventlink            *ipc_eventlink_t;
typedef struct ipc_port                 *eventlink_port_pair_t[2];
typedef struct task_id_token            *task_id_token_t;
typedef struct kcdata_object            *kcdata_object_t;

/*
 * These aren't really unique types.  They are just called
 * out as unique types at one point in history.  So we list
 * them here for compatibility.
 */
typedef processor_set_t         processor_set_name_t;

/*
 * Mig doesn't translate the components of an array.
 * For example, Mig won't use the thread_t translations
 * to translate a thread_array_t argument.  So, these definitions
 * are not completely accurate at the moment for other kernel
 * components.
 */
typedef task_t                  *task_array_t;
typedef thread_t                *thread_array_t;
typedef processor_set_t         *processor_set_array_t;
typedef processor_set_t         *processor_set_name_array_t;
typedef processor_t             *processor_array_t;
typedef thread_act_t            *thread_act_array_t;
typedef ledger_t                *ledger_array_t;

/*
 * However the real mach_types got declared, we also have to declare
 * types with "port" in the name for compatability with the way OSF
 * had declared the user interfaces at one point.  Someday these should
 * go away.
 */
typedef task_t                  task_port_t;
typedef task_array_t            task_port_array_t;
typedef thread_t                thread_port_t;
typedef thread_array_t          thread_port_array_t;
typedef ipc_space_t             ipc_space_port_t;
typedef host_t                  host_name_t;
typedef host_t                  host_name_port_t;
typedef processor_set_t         processor_set_port_t;
typedef processor_set_t         processor_set_name_port_t;
typedef processor_set_array_t   processor_set_name_port_array_t;
typedef processor_set_t         processor_set_control_port_t;
typedef processor_t             processor_port_t;
typedef processor_array_t       processor_port_array_t;
typedef thread_act_t            thread_act_port_t;
typedef thread_act_array_t      thread_act_port_array_t;
typedef semaphore_t             semaphore_port_t;
typedef ledger_t                ledger_port_t;
typedef ledger_array_t          ledger_port_array_t;
typedef alarm_t                 alarm_port_t;
typedef clock_serv_t            clock_serv_port_t;
typedef clock_ctrl_t            clock_ctrl_port_t;
typedef char vfs_path_t[4096];

/*
 * 8K, c.f. MAXLONGPATHLEN in sys/syslimits.h.
 * These types should NEVER be allocated on the stack.
 */
typedef char nspace_path_t[8192];
typedef char nspace_name_t[8192];

#define TASK_NULL               ((task_t) NULL)
#define TASK_NAME_NULL          ((task_name_t) NULL)
#define TASK_INSPECT_NULL       ((task_inspect_t) NULL)
#define TASK_READ_NULL          ((task_read_t) NULL)
#define THREAD_NULL             ((thread_t) NULL)
#define THREAD_INSPECT_NULL     ((thread_inspect_t)NULL)
#define THREAD_READ_NULL        ((thread_read_t)NULL)
#define TID_NULL                ((uint64_t) NULL)
#define THR_ACT_NULL            ((thread_act_t) NULL)
#define IPC_SPACE_NULL          ((ipc_space_t) NULL)
#define IPC_SPACE_READ_NULL     ((ipc_space_read_t) NULL)
#define IPC_SPACE_INSPECT_NULL  ((ipc_space_inspect_t) NULL)
#define COALITION_NULL          ((coalition_t) NULL)
#define HOST_NULL               ((host_t) NULL)
#define HOST_PRIV_NULL          ((host_priv_t)NULL)
#define HOST_SECURITY_NULL      ((host_security_t)NULL)
#define PROCESSOR_SET_NULL      ((processor_set_t) NULL)
#define PROCESSOR_NULL          ((processor_t) NULL)
#define SEMAPHORE_NULL          ((semaphore_t) NULL)
#define LOCK_SET_NULL           ((lock_set_t) NULL)
#define LEDGER_NULL             ((ledger_t) NULL)
#define ALARM_NULL              ((alarm_t) NULL)
#define CLOCK_NULL              ((clock_t) NULL)
#define UND_SERVER_NULL         ((UNDServerRef) NULL)
#define ARCADE_REG_NULL         ((arcade_register_t) NULL)
#define MACH_EVENTLINK_NULL     ((mach_eventlink_t) 0)
#define IPC_EVENTLINK_NULL      ((ipc_eventlink_t) NULL)
#define TASK_ID_TOKEN_NULL      ((task_id_token_t) NULL)
#define KCDATA_OBJECT_NULL      ((kcdata_object_t) NULL)

/* capability strictly _DECREASING_.
 * not ordered the other way around because we want TASK_FLAVOR_CONTROL
 * to be closest to the itk_lock. see task.h.
 */
typedef unsigned int            mach_task_flavor_t;
#define TASK_FLAVOR_CONTROL     0    /* a task_t */
#define TASK_FLAVOR_READ        1    /* a task_read_t */
#define TASK_FLAVOR_INSPECT     2    /* a task_inspect_t */
#define TASK_FLAVOR_NAME        3    /* a task_name_t */

#define TASK_FLAVOR_MAX         TASK_FLAVOR_NAME

/* capability strictly _DECREASING_ */
typedef unsigned int            mach_thread_flavor_t;
#define THREAD_FLAVOR_CONTROL   0    /* a thread_t */
#define THREAD_FLAVOR_READ      1    /* a thread_read_t */
#define THREAD_FLAVOR_INSPECT   2    /* a thread_inspect_t */

#define THREAD_FLAVOR_MAX       THREAD_FLAVOR_INSPECT

typedef int64_t                 ledger_amount_t;
#define LEDGER_LIMIT_INFINITY   ((ledger_amount_t)((1ULL << 63) - 1))

typedef char                    *user_subsystem_t;
typedef char                    *labelstr_t;
