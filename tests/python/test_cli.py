from solitaire2.cli import main


def test_missing_tool_returns_usage_error(capsys) -> None:
    assert main([]) == 2
    assert "usage:" in capsys.readouterr().out


def test_unknown_tool_returns_error(capsys) -> None:
    assert main(["missing"]) == 2
    assert "unknown tool" in capsys.readouterr().err


def test_scaffold_tool_dispatches(capsys) -> None:
    assert main(["scaffold"]) == 0
    assert "implementation pending" in capsys.readouterr().out
