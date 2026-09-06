from solitaire2 import __version__


def test_python_package_exposes_backend_version() -> None:
    assert __version__ == "0.1.0"
