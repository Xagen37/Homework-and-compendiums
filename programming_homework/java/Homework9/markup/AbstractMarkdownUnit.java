package md2html.markup;

import java.util.ArrayList;
import java.util.List;

public abstract class AbstractMarkdownUnit implements MarkdownUnit {
    protected List<MarkdownUnit> innerUnits;

    public AbstractMarkdownUnit() {
        innerUnits = new ArrayList<>();
    }

    public AbstractMarkdownUnit(List<MarkdownUnit> source) {
        innerUnits = new ArrayList<>(List.copyOf(source));
    }

    public void toMarkdown(StringBuilder source) {
        for (MarkdownUnit unit : innerUnits) {
            unit.toMarkdown(source);
        }
    }

    public void toHtml(StringBuilder source) {
        for (MarkdownUnit unit : innerUnits) {
            unit.toHtml(source);
        }
    }

    public void add(MarkdownUnit toAdd) {
        innerUnits.add(toAdd);
    }
}
