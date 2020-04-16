package markup;

import java.util.ArrayList;
import java.util.List;

public class Paragraph implements MarkdownUnit {
    protected List<MarkdownUnit> innerUnits;

    public Paragraph() {
        innerUnits = new ArrayList<MarkdownUnit>();
    }

    public Paragraph(List<MarkdownUnit> source) {
        innerUnits = new ArrayList<MarkdownUnit>(source);
    }

    @Override
    public void toMarkdown(StringBuilder source) {
        for (MarkdownUnit unit : innerUnits) {
            unit.toMarkdown(source);
        }
    }

    @Override
    public void toHtml(StringBuilder source) {
        for (MarkdownUnit unit : innerUnits) {
            unit.toHtml(source);
        }
    }
}
