#pragma once

#ifdef EXPORT_XEN_API
    #define XEN_API __declspec(dllexport)
#else
    #define XEN_API __declspec(dllimport)
#endif