#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <stdio.h>
#include <inttypes.h>

static int MAX_OUTPUT_DATA_SIZE = 0x10000;

// clang-format off
extern int OnServiceRequestReceived(
    const uint8_t* input_data,
    const int input_size,
    uint8_t output[]);

static PyObject *
zprobe_commu(PyObject* self, PyObject* args)
{
    Py_buffer in_py_buff;
    uint8_t out_buff[MAX_OUTPUT_DATA_SIZE];

    if (!PyArg_ParseTuple(args, "y*", &in_py_buff))
        return NULL;

    uint8_t* buf_ptr = (uint8_t*)(in_py_buff.buf);

    int ret = OnServiceRequestReceived(buf_ptr, in_py_buff.len, out_buff);

    return Py_BuildValue("y#", out_buff, ret);
}

static PyMethodDef ZCommMethods[] = {
    {"communicate", zprobe_commu, METH_VARARGS,
     "Send a serialized data and return the response."},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

static struct PyModuleDef zprobemodule = {
    PyModuleDef_HEAD_INIT,
    "zprobe", /* name of module */
    NULL,     /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    ZCommMethods};

PyMODINIT_FUNC
PyInit_zprobe(void)
{
    return PyModule_Create(&zprobemodule);
}
