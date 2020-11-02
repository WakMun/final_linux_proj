#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/init.h>   /* Needed for the macros */
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/interrupt.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Donald Duck");
MODULE_DESCRIPTION("A simple example Linux module.");
MODULE_VERSION("0.01");

#define LEDPin 23
#define TriggerPin 18
#define EchoPin 24

static unsigned int ULSens_irq = -1;
static u64 t_start_ns = 0L;
static u64 t_dur_ns = 0L;
static struct task_struct *thread_st;

void my_gpio_init(void);
void my_gpio_exit(void);

void my_gpio_init(void)
{
    gpio_request(TriggerPin, "TriggerPin");
    gpio_request(EchoPin, "EchoPin");
    gpio_request(LEDPin, "LED");

    gpio_direction_output(LEDPin, 0);
    gpio_direction_input(EchoPin);
    gpio_direction_output(TriggerPin, 0);

    gpio_export(LEDPin, false);
    gpio_export(EchoPin, false);
    gpio_export(TriggerPin, false);

}

void my_gpio_exit(void)
{
    gpio_set_value(LEDPin, 0x0);
    gpio_free(LEDPin);
    gpio_free(EchoPin);
    gpio_free(TriggerPin);
    free_irq(ULSens_irq, NULL);
}

irq_handler_t irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs)
{
    if (t_start_ns == 0L){
        t_start_ns = ktime_get_ns();
    }
    else
    {
        t_dur_ns = ktime_get_ns() - t_start_ns;
        //t_dur_us = t_dur_ns / 1000;
        //cms = (343 * (t_dur_us / 2)) / 10000;
        //    dist_cm = cms;
    }
    return (irq_handler_t)IRQ_HANDLED;
}

/**
 * @brief Main loop which iterates every 500msec
 * 
 * @param arg 
 * @return int 
 */
static int main_loop(void *arg)
{
    int dist_cm = 0;
    long t_dur_us = 0;
    allow_signal(SIGKILL);
    while (!kthread_should_stop())
    {
        msleep_interruptible(500);
        gpio_set_value(LEDPin, 0x1);
        //start measurement
        t_start_ns = 0L;
        gpio_set_value(TriggerPin, 1);
        udelay(10);
        gpio_set_value(TriggerPin, 0);
        msleep(50);
        gpio_set_value(LEDPin, 0x0);
        t_dur_us = t_dur_ns;
        t_dur_us = t_dur_us/1000;
        dist_cm = (343 * (t_dur_us / 2)) / 10000;
        t_start_ns = 0L;
        t_dur_ns = 0L;
        printk(KERN_INFO "Pdc_dist: %d cm", dist_cm);
        dist_cm = 0;
        if (signal_pending(thread_st))
            break;
    }
    return 0;
}

static int __init hello_init(void)
{
    int ret_val = 0;
    printk(KERN_INFO "Pdc Kernel Mod started\n");
    my_gpio_init();

    ULSens_irq = gpio_to_irq(EchoPin);
    ret_val = request_irq(ULSens_irq, (irq_handler_t)irq_handler,
                          IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
                          "irq_handler", NULL);

    if (ret_val)
    {
        printk(KERN_INFO "ERROR: Cannot register IRQ handler\n");
    }
    

    thread_st = kthread_run(main_loop, NULL, "main_loop");
    if (IS_ERR(thread_st))
    {
        printk(KERN_INFO "ERROR: Cannot create thread main_loop\n");
        ret_val = PTR_ERR(thread_st);
        thread_st = NULL;
        return ret_val;
    }

    return 0;
}

static void __exit hello_exit(void)
{
    my_gpio_exit();
    if (thread_st)
        kthread_stop(thread_st);
    printk(KERN_INFO "Exiting Pdc Kernel Mod\n");
}

module_init(hello_init);
module_exit(hello_exit);
