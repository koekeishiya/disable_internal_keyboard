#include <IOKit/hid/IOHIDValue.h>
#include <IOKit/hid/IOHIDManager.h>

void keyboard_callback(void *context, IOReturn result, void *sender, IOHIDValueRef value)
{
    // do nothing
}

CFMutableDictionaryRef match_device_with_id(int vendor_id, int product_id)
{
    CFMutableDictionaryRef dict = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
    if (!dict) return NULL;

    CFNumberRef vendor_id_ref = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &vendor_id);
    if (!vendor_id_ref) return NULL;

    CFNumberRef product_id_ref = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &product_id);
    if (!product_id_ref) return NULL;

    int usage_key = 6;
    CFDictionarySetValue(dict, CFSTR(kIOHIDVendorIDKey), vendor_id_ref);
    CFDictionarySetValue(dict, CFSTR(kIOHIDProductIDKey), product_id_ref);
    CFDictionarySetValue(dict, CFSTR(kIOHIDPrimaryUsageKey), CFNumberCreate(NULL, kCFNumberIntType, &usage_key));

    CFRelease(vendor_id_ref);
    CFRelease(product_id_ref);

    return dict;
}

int main(int argc, char **argv)
{
    IOHIDManagerRef hid_manager = IOHIDManagerCreate(kCFAllocatorDefault, kIOHIDOptionsTypeNone);
    CFMutableDictionaryRef internal_keyboard = match_device_with_id(0x05ac, 0x0342);
    IOHIDManagerSetDeviceMatching(hid_manager, internal_keyboard);
    IOHIDManagerRegisterInputValueCallback(hid_manager, keyboard_callback, NULL);
    IOHIDManagerScheduleWithRunLoop(hid_manager, CFRunLoopGetMain(), kCFRunLoopDefaultMode);
    IOHIDManagerOpen(hid_manager, kIOHIDOptionsTypeSeizeDevice);
    CFRunLoopRun();
}
