#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

static struct usb_device *device;

static int customusb_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    printk(KERN_INFO "Custom USB driver (%04X:%04X) plugged\n", id->idVendor,
                                id->idProduct);
struct usb_host_interface *my_desc;
    struct usb_endpoint_descriptor *endpoint;
    int i;

    my_desc = interface->cur_altsetting;
    printk(KERN_INFO "Usb i/f %d now probed: (%04X:%04X)\n",
            my_desc->desc.bInterfaceNumber,
            id->idVendor, id->idProduct);
    printk(KERN_INFO "ID->bNumEndpoints: %02X\n",
            my_desc->desc.bNumEndpoints);
    printk(KERN_INFO "ID->bInterfaceClass: %02X\n",
            my_desc->desc.bInterfaceClass);

    for (i = 0; i < my_desc->desc.bNumEndpoints; i++)
    {
        endpoint = &my_desc->endpoint[i].desc;

        printk(KERN_INFO "ED[%d]->bEndpointAddress: 0x%02X\n",
                i, endpoint->bEndpointAddress);
        printk(KERN_INFO "ED[%d]->bmAttributes: 0x%02X\n",
                i, endpoint->bmAttributes);
        printk(KERN_INFO "ED[%d]->wMaxPacketSize: 0x%04X (%d)\n",
                i, endpoint->wMaxPacketSize,
                endpoint->wMaxPacketSize);
    }

    device = interface_to_usbdev(interface);
    return 0;
    return 0;
}

/*static ssize_t customusb_read(struct file *f, char __user *buf, size_t cnt, loff_t *off)
{

    if (copy_to_user()
    {
        return -EFAULT;
    }
}
static ssize_t pen_write(struct file *f, const char __user *buf, size_t cnt,
                                    loff_t *off)
{

    if (copy_from_user()
    {
        return -EFAULT;
    }

}*/

static void customusb_disconnect(struct usb_interface *interface)
{
    printk(KERN_INFO "Custom USB driver removed\n");
}

static struct usb_device_id customusb_table[] =
{
    { USB_DEVICE(0x1609, 0x3a04) },
    {} 
};
MODULE_DEVICE_TABLE (usb, customusb_table);

static struct usb_driver customusb_driver =
{
    .name = "customusb_driver",
    .id_table = customusb_table,
    .probe = customusb_probe,
    .disconnect = customusb_disconnect,
};

static int __init usb_init(void)
{
    return usb_register(&customusb_driver);
}

static void __exit usb_exit(void)
{
    usb_deregister(&customusb_driver);
}

module_init(usb_init);
module_exit(usb_exit);

MODULE_LICENSE("GPL");
